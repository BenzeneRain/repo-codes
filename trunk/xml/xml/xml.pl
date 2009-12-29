#!/usr/bin/perl

use XML::Simple;
use Data::Dumper;

$xml = new XML::Simple;

$data = $xml->XMLin("configuration.xml");

print Dumper($data);
