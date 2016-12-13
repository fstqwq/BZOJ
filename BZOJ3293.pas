program BZOJ3293;
uses math;
var
	a,c:array[0..100001] of int64;
	n,i,j,k:longint;
	sum,avr,mid,ans:int64;
procedure quicksort(l,r:longint); 
var 
	i,j:longint;
	p,temp:int64;
begin
	if l>=r then exit;
	i:=l;j:=r;p:=c[random(r-l+1)+l];
	repeat
		while c[i]<p do inc(i);
		while c[j]>p do dec(j);
		if i<=j then begin
			temp:=c[i];
			c[i]:=c[j];
			c[j]:=temp;
			inc(i);dec(j);
		end;
	until i>j;
	if (i<r) then quicksort(i,r);
	if (j>l) then quicksort(l,j);
end;
begin
	randomize;
	read(n);
	sum:=0;
	for i:= 1 to n do begin
		read(a[i]);
		inc(sum,a[i]);
	end;
	avr:=sum div n;
	c[i]:=0;
	for i:= 2 to n do begin
		c[i]:=c[i-1]+a[i]-avr;
	end;
	quicksort(1,n);
	mid:=c[(n+1) div 2];
	ans:=0;
	for i:= 1 to n do begin
		inc(ans,abs(c[i]-mid));
	end;
	writeln(ans);
end.
