rm -rf result.txt

for c in {1..20}
do
./generator --big > instructions.txt
cat instructions.txt | grep -E '#Here' >> result.txt

for lemin in "$@"
do
echo "$lemin" >> result.txt
./$lemin < instructions.txt | grep -E '^L' | wc -l >> result.txt
done

done

cat result.txt
