#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use List::Util qw/sum/;
use Data::Dumper;

my $var;
{
    local $/;
    open my $fh, '<', 'input.txt' or die "can't open : $!";
    $var = <$fh>;
}

my @cards = split /\n\n/, $var;
map { s/^\s// } @cards;


my $cartegagnante;
my $num;

foreach (split /,/, shift @cards ){
	$num = $_;
	s/(\b)($num)(\b)/$1 X$3/ foreach (@cards);	
	last if( $cartegagnante = checkBingo(@cards));
}


say $cartegagnante;
say $num;

say my $sumCarte = sum($cartegagnante =~ /(\d+)/g) ;
say $sumCarte * $num;

sub checkBingo {
	my $lastCard = $_[0] unless ($#_);
	foreach my $i ( sort { $b <=> $a } (0..$#_) ){
		if ($_[$i] =~ /(X\s+){4}X\n/){
			splice(@cards, $i, 1) 
		}else{
			my @nums = split /\s+/, $_[$i] ;
			for (0..4){
				splice(@cards, $i, 1) if ($nums[0+$_] eq $nums[5+$_] eq $nums[10+$_] eq $nums[15+$_] eq $nums[20+$_] eq "X");
			}
		}
	}
	return $lastCard if ($#cards == -1);
}
