using System;
using System.Collections.Generic;

namespace Zappy.Client.MapSystem
{
	public class Map
	{
		private List<MapTile> tiles { get; set; } = new List<MapTile>();

		public int X { get { return (MapHeight_X); } }
		public int Y { get { return (MapWidth_Y); } }

		private int MapHeight_X;
		private int MapWidth_Y;

		public Map(int _x, int _y)
		{
			int height;
			int width;
			int i;

			i = 0;
			width = 0;
			height = 0;
			this.MapHeight_X = _x;
			this.MapWidth_Y = _y;
			while (i != (X * Y))
			{
				if ((i % Y) == 0 && (i != 0)) {
					width = 0;
					height++;
                    if (Constantes.IS_DEBUG)
					    Console.Write("\n");
				}
				this.tiles.Add(new MapTile(height, width));
                if (Constantes.IS_DEBUG)
				    Console.Write("  [@{0}x{1}]  ", height, width);
				width++;
				i++;
			}
            if (Constantes.IS_DEBUG)
                Console.WriteLine("\n --> Map Generated");
		}

		public MapTile GetTile(int x, int y)
		{
			if (x < 0 || y < 0)
				return (null);
			if (x > X || y > Y)
				return (null);
			foreach (MapTile tile in this.tiles)
				if (tile.X == x && tile.Y == y)
					return (tile);
			return (null);
		}
	}
}

