#!/usr/bin/perl -w

use strict;
use Socket;
use DBI;

my $addr = 'localhost';
my $port = '8192';
my $dest = sockaddr_in($port, inet_aton($addr));
my $buf = undef;
my $total = 0;
my $ac = 0;
my $wa = 0;

my $db_conn = DBI->connect("DBI:mysql:database=PID;host=localhost","PIRService","PIRssap",{'RaiseError'=>1});

srand(time ^ $$ ^ unpack "%L*", `ps axww | gzip -f`);

for(my $i = 1; $i <= $ARGV[0]; $i++)
{
	socket(SOCKFD, AF_INET, SOCK_STREAM, 6) or die "Cannot create socket: $!\n";
	connect(SOCKFD, $dest) or die "Connection Failed: $!\n";
	
	my $id = int(rand(100000));
#	my $id = $i;

	print "Query item $id\n";

	send(SOCKFD,"$id",0);

	my $bs = sysread(SOCKFD, $buf, 2048);
	my $query_str = $db_conn->prepare("SELECT item FROM data_org WHERE id=$id");
        $query_str->execute();	

	my $ref = $query_str->fetchrow_hashref();
	print "Received $bs bytes, content is \"$buf\"\n";
	print "Reference content is \"$ref->{'item'}\"\n";
	if($buf eq $ref->{'item'})
	{
		print "Test $i Passed!\n";
		$ac = $ac + 1;
	}
	else
	{
		print "Test $i Failed!\n";
		$wa = $wa + 1;
	}
	$total = $total + 1;
	print "Passed\tFailed\tTotal\n";
	print "$ac\t$wa\t$total\n\n";

	close SOCKFD;
}

$db_conn->disconnect();
