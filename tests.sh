make maptest
clear
printf '\e[1;34m%-6s\e[m' "--> Testing MapTiles ! - [RESSOURCES]"
echo ""
./1
rm -rf 1
printf '\e[1;34m%-6s\e[m' "--> Testing MapTiles ! - [PLAYERS]"
echo ""
./2
rm -rf 2
printf '\e[1;34m%-6s\e[m' "--> Testing Map ! - [GAME LOGIC]"
echo ""
./3
rm -rf 3
printf '\e[1;34m%-6s\e[m' "--> Testing Drone ! - [PLAYERS]"
echo ""
./4
rm -rf 4
