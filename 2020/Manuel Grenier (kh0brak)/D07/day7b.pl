
#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;

open(FILE, 'input.txt') or die;

my %bags;
while (<FILE>) {
	chomp;
	my ($key, $strBags) = split(/\sbags\scontain\s/, $_);
	foreach ( split(/, /,$strBags) ){
		my ($nb, $bag) = $_ =~ m/(\d)\s([\w ]+)\sbags?\.?/ ;
		$bags{$key}{$bag} = $nb if ($nb) ;
	}
}

print countBags('shiny gold')-1 ; 


sub countBags{
	my ($bagName) = @_;
	my $count = 1;	
	foreach (keys %{$bags{$bagName}}){
		$count += ($bags{$bagName}{$_} * countBags($_) );
	}
	return $count;
}
