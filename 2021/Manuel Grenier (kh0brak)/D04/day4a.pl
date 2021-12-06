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
	foreach my $card (@cards){
		$card  =~ s/(\b)($num)(\b)/$1X$3/;
	}
	last if ($cartegagnante = checkBingo(@cards));
}


say $cartegagnante ;
say $num;

say my $sumCarte = sum($cartegagnante =~ /(\d+)/g) ;
say $sumCarte * $num;

sub checkBingo {
	foreach  my $card (@_){
		return $card if $card =~ /(X\s+){4}X\n/;
		my @nums = split /\s+/, $card ;
		for (0..4){
			return $card if ($nums[0+$_] eq $nums[5+$_] eq $nums[10+$_] eq $nums[15+$_] eq $nums[20+$_] eq "X");
		}
	}
}
