#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;

open(FILE, 'input.txt') or die;

my (@rules, @messages);


my (%tiles, $noTile, @contenu);

while (<FILE>) {
	chomp;
	if (/^Tile (\d+):$/){
		$noTile = $1;		
	}elsif(my @row = /^([#.]+)$/){
		push @contenu, [split //, $1];		
	}else{
		$tiles{$noTile} = {'contenu' => [@contenu]};
		@contenu = ();		
	}
}

foreach (keys %tiles){ generateBorders($_); }
foreach (keys %tiles){ generateMatches($_); }


my $imageSize = sqrt(keys %tiles);
my $tilePixel = 10;

my @image;
push @image, [('') x $imageSize] for 1 .. $imageSize;

#trouver un coin
my $firstCorner  ;
my @corners;
foreach (keys %tiles){
	$firstCorner = $_;
	last if(scalar keys $tiles{$_}{'matches'}->%* == 2);
}

#remplir l'image
for my $x (0..$imageSize-1){
	for my $y (0..$imageSize-1){
		ruleTopCorner($firstCorner)	if ($x == 0 && $y == 0);
		ruleFirstRow($x, $y) 		if ($x == 0 && $y != 0);
		ruleFirstCol($x, $y) 		if ($x != 0 && $y == 0);
		ruleOther($x, $y) 			if ($x != 0 && $y != 0);
	} 
}



my @rawImage;
push @rawImage, [' ' x ($imageSize * ($tilePixel-2))] for 1 .. $imageSize * ($tilePixel-2);

for my $x (0..$imageSize-1){
	for my $y (0..$imageSize-1){
		next unless( defined $image[$x][$y]);
		my @contenu = $tiles{$image[$x][$y]}{'contenu'}->@*;
		for my $i (0..$tilePixel-3){
			for my $j (0..$tilePixel-3){
				$rawImage[$x*8+$i][$y*8+$j] = $contenu[$i+1][$j+1];
			}
		}
	}
}


my @montreCoor = ([0,18],[1,0],[1,5],[1,6],[1,11],[1,12],[1,17],[1,18],[1,19],[2,1],[2,4],[2,7],[2,10],[2,13],[2,16]);
my (@imageAvecMonstre) = findMonsters(@rawImage);

#Afficher l'image
foreach (@imageAvecMonstre){
	print $_->@*;
	print "\n";
}

my $roughWater = 0;
for my $x (0 .. $#imageAvecMonstre) {
	for my $y (0 ..  $#{$imageAvecMonstre[$x]}) {		
		if ($imageAvecMonstre[$x][$y] eq "#"){$roughWater++;}
	}
}
print $roughWater ;




#Afficher les tuiles
# foreach (@image){ 
	# print join(',',$_->@*);
	# print "\n";	
# }


sub findMonsters{
	my @image = @_;
	my $maxcol = ($imageSize * ($tilePixel-2)) - 19-1;
	my $maxrow = ($imageSize * ($tilePixel-2)) - 2-1;
	my $contientMonstre = 0;
	my $nbMonstre = 0;
	my @monstreLoc;
	my $i = 0;
	while ($nbMonstre == 0) {
		my $monsterPixel = 0;

		if ($i > 0 && ($i % 4 == 0 || $i % 7 == 0 ) ) { 
			@image = flipArray(@image); }
		else{ 
			@image = rotateArray(@image); 
		}	
		
		for my $x (0 .. $maxrow) {
			for my $y (0 .. $maxcol) {
				foreach (@montreCoor) {
					$contientMonstre++ if ($image[$x+$_->[0]][$y+$_->[1]] eq "#") 
				}
				if ($contientMonstre == @montreCoor) {
					$nbMonstre++;
					foreach (@montreCoor){ $image[$x + $_->[0]][$y + $_->[1]] = 'O'; }
				}
				$contientMonstre = 0;
			}
		}
		$i++;
	}
	return 	@image;
}

sub ruleTopCorner{
	my $tileKey = shift;
	 flip($tileKey);	
	until ( !defined $tiles{$tileKey}{'matches'}{'top'} && !defined $tiles{$tileKey}{'matches'}{'left'} ){
		rotate($tileKey);		
	}
	$image[0][0] = $tileKey;
}

sub ruleFirstRow{
	my ($x, $y) =  @_;
	my $voisin = $image[0][$y-1];
	my $tileKey = $tiles{$voisin}{'matches'}{'right'};
		
	my $i = 0;
	until ( !defined $tiles{$tileKey}{'matches'}{'top'} && defined $tiles{$tileKey}{'matches'}{'left'} && $tiles{$tileKey}{'matches'}{'left'} eq $voisin){
		rearrange($tileKey, $i++);
	} 
	$image[$x][$y] = $tileKey;
}


sub ruleFirstCol{
	my ($x, $y) =  @_;
	my $voisin = $image[$x-1][0];
	my $tileKey = $tiles{$voisin}{'matches'}{'bottom'};
				
	my $i = 0;
	until ( !defined $tiles{$tileKey}{'matches'}{'left'} && defined $tiles{$tileKey}{'matches'}{'top'} && $tiles{$tileKey}{'matches'}{'top'} eq $voisin){
		rearrange($tileKey, $i++);
	}
	$image[$x][$y] = $tileKey;
}

sub ruleOther{
		my ($x, $y) =  @_;
	my $voisinX = $image[$x-1][$y];
	my $voisinY = $image[$x][$y-1];
	
	my $tileKey = $tiles{$voisinX}{'matches'}{'bottom'};

	my $i = 0;
	until ( defined $tiles{$tileKey}{'matches'}{'left'} && defined $tiles{$tileKey}{'matches'}{'top'} && $tiles{$tileKey}{'matches'}{'top'} eq $voisinX && $tiles{$tileKey}{'matches'}{'left'} eq $voisinY){
		rearrange($tileKey, $i++);
	}
	$image[$x][$y] = $tileKey;
}

sub rearrange {
	my ($key, $iter) = @_;
	if ($iter > 0 && ($iter % 4 == 0 || $iter % 7 == 0 ) ) { flip($key); }
	else{ rotate($key); }		
	last if ($iter > 20);
}


sub rotate {
	my $key = shift;		
	my @contenu = $tiles{$key}{'contenu'}->@*;

	$tiles{$key}{'contenu'} = [rotateArray(@contenu)];
	delete $tiles{$key}{'border'};
	delete $tiles{$key}{'matches'};
	generateBorders($key);
	generateMatches($key);
}

sub rotateArray{
	my @contenu = @_;
	my @rot = ([]);
	for my $i (0 .. $#contenu) {
		for my $j (0 .. $#contenu){
				$rot[$j][$#contenu-$i] = $contenu[$i][$j];
		}
	}
	return @rot;
}

sub flip {
	my $key = shift;			
	my @contenu = $tiles{$key}{'contenu'}->@*;

	$tiles{$key}{'contenu'} = [flipArray(@contenu)];
	delete $tiles{$key}{'border'};
	delete $tiles{$key}{'matches'};
	generateBorders($key);
	generateMatches($key);
}

sub flipArray{
	my @contenu = @_;
	my @flip = ([]);
	for my $i (0 .. $#contenu) {
		for my $j (0 .. $#contenu){
				$flip[$i][$#contenu-$j] = $contenu[$i][$j];
		}
	}
	return @flip;
}

sub generateBorders{
	my $k = shift;
	my %borders;
	my @contenu = $tiles{$k}{'contenu'}->@*;
	
	$borders{'top'} 		= toBin(0, $contenu[0]->@*);
	$borders{'fliptop'} 	= toBin(1, $contenu[0]->@*);
	$borders{'bottom'} 		= toBin(0, $contenu[$#contenu]->@*);
	$borders{'flipbottom'}	= toBin(1, $contenu[$#contenu]->@*);
	$borders{'left'} 		= toBin(0, map { $_->[0]} @contenu);
	$borders{'flipLeft'} 	= toBin(1, map { $_->[0]} @contenu);
	$borders{'right'} 		= toBin(0, map { $_->[@{$_}-1]} @contenu);
	$borders{'flipRight'} 	= toBin(1, map { $_->[@{$_}-1]} @contenu);
	
	$tiles{$k}{'borders'} = \%borders;
}

sub generateMatches{
	my $k = shift;
	my %matches;
	foreach ('top','right','bottom','left'){
		my $match = findMatch($k, $_);		
		$matches{$_} = $match if ( $match );
	}
	$tiles{$k}{'matches'} = \%matches;
	
}

sub findMatch{
	my ($k, $side) = @_;
	foreach my $tile (keys %tiles){
		next if ($k eq $tile);
		return $tile if ( grep /^$tiles{$k}{'borders'}{$side}$/, values $tiles{$tile}{'borders'}->%* );
	}
	return undef;
}
	
sub toBin{
	my $flipped = shift;
	return oct("0b" . join('', map { $_ eq '#' ? 1 : 0 } $flipped ?  reverse @_ : @_) );	
}
	
	