
#!/usr/bin/perl

#
use strict;
use warnings;


#Charger l'input
open(FILE, 'input.txt') or die;

my %depenses;
while (<FILE>) {
 chomp;
 $depenses{$_} = 1;
}


foreach my $depense1 (keys %depenses){
	my @entries;
	my $temp_sum = 2020 - $depense1;
	map { $depenses{$temp_sum - $_} ? push (@entries,$_) : undef } keys %depenses;
	if (@entries)  {
		print $depense1 * $entries[0] * $entries[1];
		exit;
	}
	
}

