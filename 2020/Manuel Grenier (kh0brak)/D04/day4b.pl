
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
	
	my $ageValid 	= $passport->{'byr'} && 1920 <= $passport->{'byr'} <= 2002;
	my $issueValid 	= $passport->{'iyr'} && 2010 <= $passport->{'iyr'} <= 2020;
	my $expValid 	= $passport->{'eyr'} && 2020 <= $passport->{'eyr'} <= 2030;	
	my $heighValid 	= 0;
	if ($passport->{'hgt'} && substr($passport->{'hgt'}, -2) eq 'cm') { $heighValid = 150 <= substr($passport->{'hgt'},0, -2) <= 193 ;}
	elsif($passport->{'hgt'} && substr($passport->{'hgt'}, -2) eq 'in'){ $heighValid = 59 <= substr($passport->{'hgt'},0, -2) <= 76 ;}
	my $hairValid 	=  $passport->{'hcl'} && $passport->{'hcl'} =~ m/#(\d|[a-f]){6}$/;
	my $eyeValid 	= $passport->{'ecl'} && length($passport->{'ecl'}) == 3 && $passport->{'ecl'} =~ m/^(amb|blu|brn|gry|grn|hzl|oth)?$/;
	my $pidValid 	= $passport->{'pid'} && $passport->{'pid'} =~ m/^\d{9}$/;
	
	return ($ageValid && $issueValid && $expValid && $heighValid && $hairValid && $eyeValid && $pidValid	);
}
