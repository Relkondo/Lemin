./generator --big > instructions.txt
cat instructions.txt | grep -E '#Here'

for lemin in "$@"
do
echo "$lemin"
time ./$lemin < instructions.txt | grep -E '^L' | wc -l
done
