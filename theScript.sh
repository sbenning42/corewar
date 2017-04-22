echo "Get good branch"
git checkout corewar_v2
echo "Done"
echo "Create Repo"
mkdir -p TGZ
echo "Done"
echo "Compiling glines"
gcc -o givelines glines.c
echo "Done"
echo "Dumping zork. . ."
./givelines | ./corewar -s 1 -v 31 zork.cor > TGZ/zaz_zork_s1_v31
echo "Done"
echo "Dumping fluttershy. . ."
./givelines | ./corewar -s 1 -v 31 fluttershy.cor > TGZ/zaz_fluttershy_s1_v31
echo "Done"
echo "Dumping helletrain (might be long). . ."
./givelines | ./corewar -s 1 -v 31 helltrain.cor > TGZ/zaz_helltrain_s1_v31
echo "Done"
echo "Dumping game with bigzork fluttershy and helltrain (might be very very very long). . ."
./givelines | ./corewar -s 1 -v 31 bigzork.cor fluttershy.cor helltrain.cor > TGZ/zaz_game_bigzork_fluttershy_helltrain_s1_v31
echo "Done"
echo "Compressing results"
tar czvf theTarGz.tar.gz TGZ && echo "Done" && echo "Cleaning" && rm -rf TGZ && echo "Done"
echo "Add and commit"
git add theTarGz.tar.gz
git commit -m "Reverse zaz corewar with big dump"
echo "Done"
echo "Git PUSH"
git push origin corewar_v2
echo "Done"
echo "Thank's Quentin"
echo "Done"
