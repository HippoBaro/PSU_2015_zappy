using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zappy.Client.MapSystem
{
    public static class MapMath
    {
        /* CAUTION !
        **
        ** Those functions do not take in consideration the actual rotation of the player.
        ** There all based on the map it-self :
        **
        **				 TOP
        **	LEFT		  X			RIGHT
        **				BOTTOM
        */

        public static MapTile GetTopTile(Map world, MapTile tile)
        {
            int X;

            if (tile.X == 0)
                X = world.X - 1;
            else
                X = tile.X - 1;
            Console.WriteLine("[DEGUG] --> @{0}x{1}", X, tile.Y);
            return (world.GetTile(X, tile.Y));
        }

        public static MapTile GetBottomTile(Map world, MapTile tile)
        {
            int X;

            if (tile.X == (world.X - 1))
                X = 0;
            else
                X = tile.X + 1;
            return (world.GetTile(X, tile.Y));
        }

        public static MapTile GetLeftTile(Map world, MapTile tile)
        {
            int Y;

            if (tile.Y == 0)
                Y = world.Y - 1;
            else
                Y = tile.Y - 1;
            return (world.GetTile(tile.X, Y));
        }

        public static MapTile GetRightTile(Map world, MapTile tile)
        {
            int Y;

            if (tile.Y == (world.Y -1))
                Y = 0;
            else
                Y = tile.Y + 1;
            return (world.GetTile(tile.X, Y));
        }

    }
}
