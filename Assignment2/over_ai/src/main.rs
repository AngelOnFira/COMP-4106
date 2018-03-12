//use std::process;

fn main() {

    //1 is my units
    //2 is enemy space
    //0 is empty space
    let board: [[i8;6]; 6] = [
    [2,2,2,2,2,2],
    [2,1,0,0,1,2],
    [2,0,0,0,0,2],
    [2,0,0,0,0,2],
    [2,1,0,0,1,2],
    [2,2,2,2,2,2]];

    alphabeta(board, 3, -10000, 10000, true);
}

fn alphabeta(board: [[i8;6]; 6], depth: i8, alpha: i8, beta: i8, max: bool) {
    if depth == 0 {
        return get_heuristic(board);
    }

    let mut children = find_possible_moves(board);

    children.len() == 0 {
        return get_heuristic(board);
    }

    if max {
        let mut v = -10000;
        while (!children.is_empty()) {
            let child = children.pop().unwrap();
            v = max(v, alphabeta(child, depth - 1, alpha, beta, false);
            alpha = max(alpha, v);
            if (beta <= alpha) {
                break;
            }
        }
        return v;
    }
    else {
        let mut v = 10000;
        while (!children.is_empty()) {
            let child = children.pop().unwrap();
            v = min(v, alphabeta(child, depth - 1, alpha, beta, true);)
            beta = min(beta, v);
            if (beta <= alpha) {
                break;
            }
        }
        return v;
    }
}

fn find_possible_moves(board: [[i8;6]; 6]) -> Vec<[[i8; 6]; 6]> {
    let mut children = Vec::new();

    for row in 0..board.len() - 1 {
        for col in 0..board[0].len() - 1 {
            if board[row][col] == 1 {
                //Simulates a piece being pushed all the way to one side
                let mut new_children = push_piece(row, col, board);
                while !new_children.is_empty() {
                    children.push(new_children.pop().unwrap());
                }
            }
        }
    }
    //println!("len {}", children.len());
}

fn push_piece(row: usize, col: usize, board: [[i8;6]; 6]) -> Vec<[[i8; 6]; 6]> {
    let mut children = Vec::new();
    let mut child_board = board;

    //Test pushing in all four directions
    'outer1: for x in (0..col + 1).rev() {
        let mut last = 0;
        //Simulates one push
        'inner1: for remove in (0..x + 1).rev() {
            let curr = child_board[row][remove];
            child_board[row][remove] = last;
            last = curr;
            //Check if we have just pushed into an empty position
            if last == 0 {
                /*
                print_board(child_board);
                println!("left: {}", x);
                println!("remove: {}", remove);
                println!("last: {}", last);
                println!("pushed empty");
                println!("");
                println!("");
                */
                break 'inner1;
            }
        }
        //Break to outer if we have pushed one of our own off
        //the board, don't add it to children to look at
        if last == 1 {
            /*
            print_board(child_board);
            println!("left: {}", x);
            println!("last: {}", last);
            println!("pushed our own");
            println!("");
            println!("");
            */
            break 'outer1;
        }
        //If we pushed an enemy off the board, add as a
        //child
        else if last == 2 {
            /*
            print_board(child_board);
            println!("left: {}", x);
            println!("last: {}", last);
            println!("pushed off enemy");
            */
            children.push(child_board);
        }
    }

    child_board = board;
    'outer2: for x in col..6 {
        let mut last = 0;
        //Simulates one push
        'inner2: for remove in x..6 {
            let curr = child_board[row][remove];
            child_board[row][remove] = last;
            last = curr;
            //Check if we have just pushed into an empty position
            if last == 0 {
                break 'inner2;
            }
        }
        //Break to outer if we have pushed one of our own off
        //the board, don't add it to children to look at
        if last == 1 {
            break 'outer2;
        }
        //If we pushed an enemy off the board, add as a
        //child
        else if last == 2 {
            children.push(child_board);
        }
    }

    child_board = board;
    'outer3: for y in (0..row + 1).rev() {
        let mut last = 0;
        //Simulates one push
        'inner3: for remove in (0..y + 1).rev() {
            let curr = child_board[remove][col];
            child_board[remove][col] = last;
            last = curr;
            //Check if we have just pushed into an empty position
            if last == 0 {
                break 'inner3;
            }
        }
        //Break to outer if we have pushed one of our own off
        //the board, don't add it to children to look at
        if last == 1 {
            break 'outer3;
        }
        //If we pushed an enemy off the board, add as a
        //child
        else if last == 2 {
            children.push(child_board);
        }
    }

    child_board = board;
    'outer4: for y in row..6 {
        let mut last = 0;
        //Simulates one push
        'inner4: for remove in y..6 {
            let curr = child_board[remove][col];
            child_board[remove][col] = last;
            last = curr;
            //Check if we have just pushed into an empty position
            if last == 0 {
                break 'inner4;
            }
        }
        //Break to outer if we have pushed one of our own off
        //the board, don't add it to children to look at
        if last == 1 {
            break 'outer4;
        }
        //If we pushed an enemy off the board, add as a
        //child
        else if last == 2 {
            children.push(child_board);
        }
    }
    return children;
}

fn get_heuristic(board: [[i8;6]; 6]) -> f32 {
    //TODO
    return 1;
}

fn print_board(board: [[i8;6]; 6]) {
    println!("__________");
    for row in 0..6 {
        for col in 0..6 {
            print!("{}", board[row][col]);
        }
        println!("");
    }
    println!("__________")
}

//fn findChildren(board: )