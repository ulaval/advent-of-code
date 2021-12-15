#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use List::Uniq ':all';
use Data::Dumper;

open(FILE, 'input.txt') or die;
my %links;
my %paths;


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

explore('start','start');

say "Reponse: ".(scalar keys %paths);

sub explore {
	my ($link, $sourcePath) = @_;
	foreach my $path (@{$links{$link}}){
		if($path eq 'end'){
			$paths{$sourcePath.",$path"}=1;
		}

		my @a = $sourcePath =~ /([a-z]+)/g  ;
		my $maxSmall = $#a == $#{uniq(@a)} ? 1 : 0; 
		my $a = () = $sourcePath =~ /$path/g;
		unless ($path eq lc $path && $a > $maxSmall ){
			explore($path, $sourcePath.",$path");
		}
	}
}

