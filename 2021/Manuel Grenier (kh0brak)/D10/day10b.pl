#!/usr/bin/perl
use v5.32.0;
use strict;
use warnings;
use Switch;
use Data::Dumper;

open(FILE, 'input.txt') or die;

my @scores;
while (<FILE>) {
	chomp;
	while ( s/(\(\)|\[\]|\{\}|\<\>)//g ){}
	next if (/\)|\]|\}|\>/);
	my $closing = scalar reverse("$_");
	$closing =~ s/\(/\)/g;
	$closing =~ s/\[/\]/g;
	$closing =~ s/\{/\}/g;
	$closing =~ s/\</\>/g;
	my $score = 0;
	foreach (split //, $closing){
		$score *= 5;
		switch($_){
			case ")" {$score += 1;}
			case "]" {$score += 2;}
			case "}" {$score += 3;}
			case ">" {$score += 4;}
		}
	}
	push @scores, int($score);
}
@scores = sort { $a <=> $b } @scores;
say $scores[$#scores/2];
