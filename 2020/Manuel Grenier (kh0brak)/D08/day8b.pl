
#!/usr/bin/perl

#
use strict;
use warnings;
use Data::Dumper;
use Storable qw(dclone);

open(FILE, 'input.txt') or die;

my @instructions;
while (<FILE>) {
	chomp;
	my ($inst, $val) = ($_ =~ /^(\w{3})\s\+?(-?\d+)$/ ) ;
	
	push (@instructions, {inst => $inst, val => int($val), ct => 0});
}

my @possibleChange;
for my $i (0..@instructions-1){
	push(@possibleChange,$i) if( $instructions[$i]{inst} =~ /nop|jmp/ );	
}


foreach (@possibleChange){
	print  runProgram($_, @instructions);
}


sub runProgram{
	my $change = shift;
	my @instructions = @{ dclone(\@_) } ;
	$instructions[$change]{inst} = $instructions[$change]{inst} eq 'nop' ? 'jmp' : 'nop';	

	my ($acc, $i) = (0, 0);
	while ( $i < @instructions &&  $i >= 0 ) {	
		if ( $instructions[$i]{ct}++ > 0 ) {return '';};
		if 		($instructions[$i]{inst} eq 'acc') { $acc += $instructions[$i]{val}; }
		elsif 	($instructions[$i]{inst} eq 'jmp'){ $i  += ($instructions[$i]{val}-1); } 
		$i++;
	}
	return $acc;
}



