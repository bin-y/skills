/**
 * Definition for a binary tree node.
 * function TreeNode(val) {
 *     this.val = val;
 *     this.left = this.right = null;
 * }
 */


function walk_leaf_find_sum(path, answer, node, sum_to_find) {
  path.push(node.val);
  if (node.left) {
    walk_leaf_find_sum(path, answer, node.left, sum_to_find - node.val);
  }
  if (node.right) {
    walk_leaf_find_sum(path, answer, node.right, sum_to_find - node.val);
  }
  else if (!node.left && sum_to_find == node.val) {
    answer.push([...path]);
  }
  path.pop();
  return;
}

/**
* @param {TreeNode} root
* @param {number} sum
* @return {number[][]}
*/
const pathSum = function (root, sum) {
  let answer = [];
  if (root) {
    walk_leaf_find_sum([], answer, root, sum);
  }
  return answer;
};