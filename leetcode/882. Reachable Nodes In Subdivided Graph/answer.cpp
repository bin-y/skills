struct node_t_;
typedef struct path_t_ {
  uint32_t length;
  uint32_t unreached_count;
  uint32_t big_to_small_reached;
  uint32_t small_to_big_reached;
  node_t_* big;
  node_t_* small;
} path_t;

typedef struct node_t_ {
  uint8_t reached;
  bool pending;
  uint32_t moves_left_on_reach;
  vector<path_t*> paths;

  node_t_():
    reached(0),
    moves_left_on_reach(0),
    pending(false)
  {

  }
} node_t;
    
class Solution {
public:
  int reachableNodes(vector<vector<int>>& edges, int M, int N) {
    unique_ptr<node_t[]> nodes_(new node_t[N]);
    auto nodes = nodes_.get();
    
    auto edge_size = edges.size();
    vector<path_t> all_paths(edge_size);
    memset(&all_paths[0], 0, sizeof(path_t) * edge_size);
    
    for (auto i = 0; i < edge_size; i++) {
      const auto& edge = edges[i];
      auto& a = nodes[edge[0]];
      auto& b = nodes[edge[1]];
      
      auto& path = all_paths[i];
      path.length = edge[2];
      path.unreached_count = edge[2];
      path.big = &b;
      path.small = &a;
      
      a.paths.push_back(&path);
      b.paths.push_back(&path);
    }
    queue<node_t*> pending_nodes;
    
    nodes[0].moves_left_on_reach = M;
    pending_nodes.push(&nodes[0]);
    
    do {
      auto from = pending_nodes.front();
      pending_nodes.pop();
      auto moves_left = from->moves_left_on_reach;
      from->reached = 1;
      from->pending = false;

      for (auto& path_ptr : from->paths) {
        auto& path = *path_ptr;
        if (path.unreached_count) {
          auto& already_reached = from == path.big ? path.big_to_small_reached : path.small_to_big_reached;
        
          if (moves_left > already_reached) {
            auto new_reach_count = min(path.unreached_count, moves_left - already_reached);
            path.unreached_count -= new_reach_count;
            already_reached += new_reach_count;
          }
        }
        
        if (path.length < moves_left) {
          auto to = from == path.big ? path.small : path.big;
          auto moves_left_after_move = moves_left - path.length - 1;
          
          if (to->moves_left_on_reach < moves_left_after_move) {
            to->moves_left_on_reach = moves_left_after_move;
            if (!to->pending) {
              pending_nodes.push(to);
              to->pending = true;
            }
          }
          else if (!to->reached) {
            to->reached = 1;
          }
        }
      }
    } while(pending_nodes.size());
    
    auto result = 0;
    for (const auto& path : all_paths) {
      result += path.length - path.unreached_count;
    }
    for (auto i = 0; i < N; i++) {
      result += nodes[i].reached;
    }
    return result; 
  }
};