var astar = {
   init: function(grid) {
      var newGrid = [][];
      for (var x = 0; x < grid.width; x++) {
         for (var y = 0; y < grid.height; y++) {
            //If wall, grid[x][y] = 1;
            //If empty space, grid[x][y] = 0;
            newGrid[x][y] = grid.get(x, y);
            newGrid[x][y].f = 0;
            newGrid[x][y].g = 0;
            newGrid[x][y].h = 0;
            newGrid[x][y].parent = null;
         }
      }
   },

   search: function(grid, start, end) {
     var searchGrid = astar.init(grid);
     
     var openList = [];
     var closedList = [];
     openList.push(start);
     
     while (openList.length > 0) {
         
         //Grab the lowest f(x) to process next
         var lowInd = 0;
         for (var i=0; i < openList.length; i++) {
             if (openList[i].f < openList[lowInd].f)
                 lowInd = i;
         }
         var currentNode = openList[lowInd];
         
         //End case -- result has been found, return the traced path
         if (currentNode == end) {
             var curr = currentNode;
             var ret = [];
             while (curr.parent) {
                 ret.push(curr);
                 curr = curr.parent;
             }
             return ret.reverse();
         }
         
         //Normal case -- move currentNode from open to closed process each of its neighbors
         openList.splice(currentNode, 1);
         
         closedList.push(currentNode);
         var neighbors = neighbors(grid, currentNode);
         
         for (var i=0; i<neighbors.length; i++) {
            var neighbor = neighbors[i];
             
            for (var j =0; j < closedList.length; j++) {
               if (closedList[j] == neighbor || neighbor == 1)
                  continue;
            }
            if (closedList[neighbor] || neighbor.isWall()) //"isWall" is unnecessary bc we've already determined what is/isn't a wall
               continue; //Change "findGraphNode" - include "graph.js" or look at source and ctrl+c > ctrl+v
         
            //g score is the shortest distance from start to current node, we need to check if
            //the path we have arrived at this neighbor is the shortest one we have seen yet
            var gScore = currentNode.g + 1; //1 is the distance from a node to it's neighbor
            var gScoreIsBest = false;
         
            if (!openList.findGraphNode(neighbor)) {
               //This is the first time we have arrived at this node, it must be the best
               //Also, we need to take the h (heuristic) score since we haven't done so yet
             
               gScoreIsBest = true;
               neighbor.h = heuristic(neighbor, end);
               openList.push(neighbor);
            } else if (gScore < neighbor.g)
               gScoreIsBest = true;
         
            if (gScoreIsBest) {
               //Found an optimal (so far) path to this node. Store info on how we got here and
               //just how good it really is
               neighbor.parent = currentNode;
               neighbor.g = gScore;
               neighbor.f = neighbor.g + nieghbor.h;
            }
         }
      }

      //No result was found -- empty array signifies failure to find path
      return [];
     
       },
       heuristic: function(pos0, pos1) {
           //This is the Manhattan distance
           var d1 = Math.abs(pos1.x - pos0.x);
           var d2 = Math.abs(pos1.y - pos0.y);
           return d1+d2;
       },
       neighbors: function(grid, node) {
           var ret = [];
           var x = node.pos.x;
           var y = node.pos.y;
        
           if(grid[x-1][y] && grid[x-1][y]) {
             ret.push(grid[x-1][y]);
           }
           if(grid[x+1][y] && grid[x+1][y]) {
             ret.push(grid[x+1][y]);
           }
           if(grid[x][y-1] && grid[x][y-1]) {
             ret.push(grid[x][y-1]);
           }
           if(grid[x][y+1] && grid[x][y+1]) {
             ret.push(grid[x][y+1]);
           }
           return ret;
       }
   };

}