#!/usr/bin/perl

use strict;
use warnings;

use 5.010;

print "// Generated with ./extractVariables.pl " . $ARGV[0] . "\n";

my $showString = 0;
my $outputString = "";
my $currentVariableName = "";
my $currentVariableContent = "";

while (my $string = <>) {
	if($showString) {
		if ($string =~ m/\sreturn\s/) {
			$showString = 0;
			next;
		}

		if($string =~ m/^\s#/ || $string =~ m/^\s$/){
			if($currentVariableName){
				$outputString .= "\n";
				$currentVariableName = "";
			}
			$string =~ s/#/\/\//;
			$outputString .= $string;
			next;
		}

		$string =~ s/\$\{RKHROOTDIR\}//;

		if($string =~ m/^\s(\w*)=(.*)$/){
				$currentVariableName = $1;
				$currentVariableContent = $2;
				$currentVariableContent =~ s/^\"//;
				$currentVariableContent =~ s/\"\s*$//g;
				$currentVariableContent =~ s/\\/\\\\/g;
				if(!$currentVariableContent){
					$currentVariableName = "";
					next;
				}
				$string =~ s/\t+//g;
				$outputString .= "this->rkvars.insert(std::pair<std::string, std::string>(\"" . $currentVariableName . "\", \"" . $currentVariableContent . "\"));\n";
		}elsif($currentVariableName){
				$string =~ s/\t+//g;
				$string =~ s/\\/\\\\/g;
				$string =~ s/\"\s*$//g;
				$string =~ s/\n//g;
				$string =~ s/^(\s*)//g;
				$currentVariableContent = $string;
				$outputString .= "this->rkvars.insert(std::pair<std::string, std::string>(\"" . $currentVariableName . "\", \"" . $currentVariableContent . "\"));\n";
		}else{
			die
		}
	}else{
		if ($string =~ m/^do_system_check_initialisation\(\).*$/) {
			$showString = 1;
		}
	}
} 


print $outputString;
