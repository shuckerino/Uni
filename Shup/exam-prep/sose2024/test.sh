x='start'
y='start2'
idx=2
export idx
export x
echo Hallo Welt > TMPFILE
echo End >> TMPFILE
while read x
do
	echo $idx: $x
	idx=`expr $idx + 1`
	y="$x"
done < TMPFILE

echo x=$x
echo y=$y
echo idx=$idx
