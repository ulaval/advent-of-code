
#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;

my @terrain;

open(FILE, 'input.txt') or die;


#Split en passports
my @passports ;
my $i = 0;
while (<FILE>) {
	chomp;
	$i++ if !$_;
	$passports[$i] .= " ".$_;
}

#Extrait les champs
foreach (@passports){
	my %fields;
	foreach ( split(' ', $_) ) {
		my ($key, $value) =  split(':', $_);
		$fields{"$key"} = $value;		
	};
	$_ = \%fields;	
}

print scalar ( grep { validatePassport($_) } @passports );


sub validatePassport{
	my $passport = shift;
	return (
		$passport->{'byr'} &&
		$passport->{'iyr'} &&
		$passport->{'eyr'} &&
		$passport->{'hgt'} &&
		$passport->{'hcl'} &&
		$passport->{'ecl'} &&
		$passport->{'pid'} 
	);
	

}
