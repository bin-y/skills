/**
 * @param {number} rowIndex
 * @return {number[]}
 */

var getRow = function (rowIndex) {
  let result = rowIndex > 10 ? new Int32Array(rowIndex + 1) : Buffer.allocUnsafe(rowIndex + 1);
  result[0] = 1;
  if (rowIndex > 0) {
    const vector_index_max = rowIndex;
    const target_row = rowIndex;
    let current_row_to_fill = 1
    let formal_length = 1;
    function fill_row_element() {
      let length =  0|(current_row_to_fill / 2) + 1;
      let write_to_right = current_row_to_fill & 1;
      if (write_to_right) {
        for (let i = 0; i < length; i++) {
          let left = 0;
          if (i > 0) {
            left = result[i - 1];
          }

          let right = left;
          if (i < formal_length) {
            right = result[i];
          }
          result[vector_index_max - i] = left + right;
        }
      }
      else {
        for (let i = 0; i < length; i++) {
          let left = 0;
          if (i > 0) {
            left = result[vector_index_max - i + 1];
          }

          let right = left;
          if (i < formal_length) {
            right = result[vector_index_max - i];
          }
          result[i] = left + right;
        }
      }

      if (current_row_to_fill == target_row) {
        for (let i = 0; i < length; i++) {
          if (write_to_right) {
            result[i] = result[vector_index_max - i];
          }
          else {
            result[vector_index_max - i] = result[i];
          }
        }
        return;
      }
      else {
        formal_length = length;
        current_row_to_fill++;
        return fill_row_element();
      }
    }
    fill_row_element();
  }
  return [...result];
};