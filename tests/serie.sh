for (( c=1; c<=20; c++ ))
do
./generator --big-superposition > instructions.txt
cat instructions.txt | grep -E '#Here' >> result.txt

for lemin in "$@"
do
echo "$lemin" >> result.txt
./$lemin < instructions.txt | grep -E '^L' | wc -l >> result.txt
done

done

cat result.txt
