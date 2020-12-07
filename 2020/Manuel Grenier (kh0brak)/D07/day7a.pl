
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

print scalar  grep { containBag($_, 'shiny gold')  } keys %bags ;

sub containBag{
	my ($bagName, $lookup) = @_;
	if ($bags{$bagName}{$lookup}){return 1}
	else{
		return grep { containBag($_, $lookup)  } keys %{$bags{$bagName}};
	};
	
}



