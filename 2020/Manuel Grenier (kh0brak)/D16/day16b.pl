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

my @validTickets = grep { isValid(@$_) } @nearby;



my %solved;
while(scalar keys %solved != scalar keys %rules ){	
	for my $position (0 .. $#my){
		next if (grep {$_ == $position } values %solved);

		my @validRules;		
		foreach my $rule ( sort keys %rules) {
			next if (defined  $solved{$rule});		
			my $fitsAll = 1;			
			foreach my $ticket (@validTickets){
				unless ($rules{$rule}->[0] <= $ticket->[$position] <= $rules{$rule}->[1] || $rules{$rule}->[2] <= $ticket->[$position] <= $rules{$rule}->[3]){
					$fitsAll = 0;
					last;
				}							
			}
			push @validRules, $rule if($fitsAll);

		}
		$solved{$validRules[0]} = $position if(@validRules == 1);	
	}
}

#print Dumper (\%solved);

my $sum = 1;
foreach (grep {$_ =~ /departure/} (keys %rules)){
	$sum *= $my[$solved{$_}];	
}
print $sum;

sub isValid{
	my @ticket = @_;
	
	foreach my $num (@ticket){
		my $valid = 0;	
		foreach my $rule (values %rules){
			$valid = 1 if ($rule->[0] <= $num <= $rule->[1] || $rule->[2] <= $num <= $rule->[3]);
		}
		return 0 unless ($valid);
	}
	return 1;
}


