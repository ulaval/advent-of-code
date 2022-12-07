#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use Switch;
use Data::Dumper;

open(FILE, 'input2.txt') or die;
my %links;
my @paths;


while (<FILE>) {
	chomp;
	my ($a,$b) = split /-/;
	
	unless ($a eq 'end' || $b eq 'start'){
		$links{$a} = [] unless exists $links{$a};
		push @{$links{$a}}, $b;
	}
	unless ($b eq 'end' || $a eq 'start'){
		$links{$b} = [] unless exists $links{$b};
		push @{$links{$b}}, $a ;
	}
}

say Dumper(\%links);

explore('start','start');

say "Reponse: ".($#paths+1);

sub explore {
	my ($link, $sourcePath) = @_;
	foreach my $path (@{$links{$link}}){
		push @paths, $sourcePath.",$path" 		if($path eq 'end');
		explore($path, $sourcePath.",$path")	unless ($path eq lc $path && $sourcePath =~ /$path/);
	}
}

