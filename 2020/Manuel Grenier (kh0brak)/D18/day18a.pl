#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use Storable qw(dclone);

open(FILE, 'input.txt') or die;

my $sum = 0;
while (<FILE>) {
	chomp;
	$sum += evaluate($_ );
}
print $sum;

sub evaluate{
	my $equation = shift;
	return $equation if $equation =~ /^\d+$/;
	
	
	while (my ($oper) = $equation =~ /(\([^()]+\))/ ){
		$oper =~ s/[\(\)]//g;
		my $res = evaluate( $oper );
		$equation =~ s/(\([^()]+\))/$res/;
	}
	
	while (my ($oper) = $equation =~ /(\d+ [*+] \d+)/){
		my $res = eval($oper);
		$equation =~ s/(\d+ [*+] \d+)/$res/;	
	}
	
	return $equation;
}

sub removeParenthese{
	my $equation = shift;
	while (my ($oper) = $equation =~ /\((\d+)\)/){
		$equation =~ s/(\(\d+\))/$oper/;	
	}
	return $equation;
}




