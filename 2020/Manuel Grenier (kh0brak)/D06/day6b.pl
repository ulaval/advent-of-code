
#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;

open(FILE, 'input.txt') or die;

my @groups ;
my $i = 0;
while (<FILE>) {
	chomp;
	if (!$_) { $i++ }
	else{
		$groups[$i]{'char'} .= $_; 
		$groups[$i]{'nb'}++; 
	}
}

my $sum = 0;
foreach my $group (@groups)  {  
	my %occ; 
	map { $occ{$_}++ } (split //, $group ->{'char'});
	foreach (keys %occ) {
		delete $occ{$_} unless ($occ{$_} == $group->{'nb'});
	}
	$sum += keys %occ;
} 
	
print $sum ;




