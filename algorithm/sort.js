function insertion (input) {
    var sorted = [input[0]];

    for(var i = 1, len1 = input.length; i < len1; i ++) {
        var _input = input[i];

        for(var j = sorted.length; j >= 0; j --) {
            var _sorted = sorted[j];

            if(_sorted <= _input) {
                sorted.splice(j + 1, 0, _input)
                break;
            }

            if(j === 0) {
                sorted.splice(0, 0, _input)
            }
        }
    }

    return sorted;
};

function selection (input) {
    for(var i = 0, len = input.length; i < len; i ++) {
        var min = i;

        for(var j = i + 1; j < len; j ++) {
            if(input[min] >= input[j]) {
                min = j;
            }
        }

        input[i] = [input[min], input[min] = input[i]][0];
    }

    return input;
};


function bubble(input) {
    for (var i = 0, len = input.length; i < len - 1; i++) {

        for (var j = i + 1; j < len; j++) {

            if(input[j] < input[i]) {

            input[j] = [input[i], input[i] = input[j]][0];

            }

        }

    }

    return input;
};

function shell(input) {
    var h = 1;
    var len = input.length;

    while(h < Math.floor(len / 3)) {
        h = h * 3 + 1;
    }
    
    while(h >= 1) {
        for(var i = h; i < len; i++)  {
            for(var j = i; j >= h; j -= h) {
                if(input[j] < input[j - h]) {
                  input[j] = [input[j - h], input[j - h] = input[j]][0];
                }
            }
        }

        h = Math.floor(h / 3);
    }

    return input;
};

function merge(input1, input2) {
    var i = 0, 
        j = 0;

    var output = [];

    while(i < input1.length || j < input2.length) {
        if(i == input1.length) {
            output.push(input2[j++]);
            continue;
        }

        if(j == input2.length) {
            output.push(input1[i++]);
            continue;
        }

        if(input1[i] < input2[j]) {
            output.push(input1[i++]);
        } else {
            output.push(input2[j++]);
        }
    }

    return output;
};

function quicksort(input) {
    sort(0, input.length - 1);
    
    return input;

    function sort(start, end) {
        if(start >= end) {
            return;
        }

        var mid = partition(start, end);

        sort(start, mid - 1);
        sort(mid + 1, end);
    }

    function partition(start, end) {
        var i = start, 
            j = end + 1, 
            k = input[start];
        
        while(true) {
            while(input[++i] < k) {
                if( i === end) break;
            }

            while(input[--j] > k) {
                if( j === start) break;
            }
            
            if(i >= j) {
                break;
            }
            
            input[i] = [input[j], input[j] = input[i]][0];
        }

        input[j] = [input[start], input[start] = input[j]][0];

        return j;
    }
};

function priorityQueueAdd(input) {
    var output = [];

    output[1] = input[0];

    for (var i = 1, len = input.length; i < len; i++) {
        output = swim(output, input[i]);
    }

    return output;

    function swim(arr, val) {
        arr.push(val);
        var k = arr.length - 1;

        while(k > 1 && arr[k >> 1] < arr[k]) {
            var p = k >> 1;

            arr[p] = [arr[k], arr[k] = arr[p]][0];

            k = p;
        }

        return arr;
    }
};