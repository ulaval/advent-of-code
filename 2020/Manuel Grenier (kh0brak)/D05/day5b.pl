
#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use List::Util qw(max min);

my @terrain;

open(FILE, 'input.txt') or die;
chomp(my @inputs = <FILE>);

my @sieges;


my @seatIDs = map { seatID(calcRow( split //, substr($_, 0, 7) ), calcCol( split //, substr($_, -3) ) ); } @inputs;
for my $x ( min(@seatIDs) ..  max(@seatIDs)){
	print $x if ( ! grep {$_ == $x} @seatIDs);
}

my @sieges;
foreach (@inputs){
	$sieges[calcRow( split //, substr($_, 0, 7) )][calcCol( split //, substr($_, -3) )] = "[]";
}
for my $x ( 0.. 127 ){
	print "Rangee $x : ";
	for my $y ( 0.. 7 ){
			print $sieges[$x][$y]? $sieges[$x][$y] : "  " ;
	}
	print "\n";
}



sub calcRow{
	my @rows = @_;
	my ($min, $max) = (0, 127);
	foreach (@rows) {
		($min, $max) = $_ eq 'F' ? ($min, $max - (($max - $min + 1 )/ 2) ) : ( $min + (($max - $min + 1 )/ 2), $max );		
	}
	return $min;
}


sub calcCol{
	my @cols = @_;
	my ($min, $max) = (0, 7);
	foreach (@cols) {
		($min, $max) = $_ eq 'L' ? ($min, $max - (($max - $min + 1 )/ 2) ) : ( $min + (($max - $min + 1 )/ 2), $max );		
	}
	return $min;
	
}

sub seatID{
	return $_[0] * 8 + $_[1] ;
}



