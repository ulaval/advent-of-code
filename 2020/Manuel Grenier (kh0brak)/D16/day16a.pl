#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;

my %nums;
my (%rules, @my, @nearby, $state);



open(FILE, 'input.txt') or die;
$state = 'rules';

while (<FILE>) {
	chomp;
	$state = 'my' if ($_ =~ /^your ticket:$/ ) ;
	$state = 'nearby' if ($_ =~ /^nearby tickets:$/ ) ;

	if($state eq 'rules'){
		my ($name, @rule) = ($_ =~ /^(\D+): (\d+)-(\d+) or (\d+)-(\d+)$/ );
		$rules{$name} = [@rule] if ($name);
	}	
	if($state eq 'my' and $_  =~ /^(\d+,?)+$/){
		@my = split(/,/, $_);
	}
	if($state eq 'nearby' and $_  =~ /^(\d+,?)+$/){
		push(@nearby, [split(/,/, $_)]);
	}
}

my %validnum;
foreach my $rule (values %rules){
	foreach ($rule->[0] .. $rule->[1], $rule->[2] .. $rule->[3]) { $validnum{$_} = 1; }
}

my $sum = 0;
foreach my $num (findAllNum()){
	$sum += $num unless (defined $validnum{$num});
}
print $sum;

sub findAllNum{
	my @nums;
	foreach my $ticket (@nearby){
		foreach (@$ticket){
			push (@nums, $_);
		}
	}
	return @nums;
}

