fn main() {
    println!("Hello, world!");
    println!("{}", add(1, 2));

    //1 is my units
    //0 is enemy space
    //2 is empty space
    let board: [[i8;6]; 6] = [
    [1,1,1,1,1,1],
    [1,1,1,1,1,1],
    [1,1,1,1,1,1],
    [0,0,0,0,0,0],
    [0,0,0,0,0,0],
    [0,0,0,0,0,0]];

    find_possible_moves(board);
}

fn add(x: i8, y: i8) -> i8 {
    x + y
}

//fn minimax(board: [[i8;6]; 6])

fn find_possible_moves(board: [[i8;6]; 6]) {
    let mut children_to_add = Vec::new();
    let mut children = Vec::new();
    let mut empty_spaces = 0;

    let mut last_board = board;
    new_board[2][2] = 4;

    for row in 0..board.len() - 1 {
        for col in 0..board[0].len() - 1 {
            if board[row][col] == 1 {
                'outer: for up in 0..row {
                    let mut child_board = board;
                    let last = 0;
                    'inner: for remove in row..0 {
                        if row != 0 {
                            last = child_board[remove - 1][col];
                            child_board[remove - 1][col] = child_board[remove][col];
                        }
                        //Break to outer if we have pushed one of our own off
                        //the board, don't add it to children to look at
                        else {
                            if last == 1 {
                                break 'outer;
                            }
                        }
                        //Check if we have just pushed an empty position
                        if last == 2 {
                            break 'inner;
                        }
                    }
                    if board[up][col] == 0 {
                        children_to_add.push(up);
                    }
                    else if board[up][col] == 2 {
                        empty_spaces++;
                    }
                    else {
                        break;
                    }
                }
                while !children_to_add.empty() {
                    let child_to_add = children_to_add.pop();
                    for i in 0..row
                }



                for down in row..board.len() - 1 {
                    if board[row][col]
                }
                for left in 0..col {
                    if board[up][col] 
                }
                for right in coll..board[0].len() - 1 {
                    if board[row][col]
                }
            }
        }
    }
}

fn create_child(row: bool, index: i8, start: i8, offset: i8) {

}

fn print_board(board: [[i8;6]; 6]) {
    for row in 0..6 {
        for col in 0..6 {
            print!("{}", board[row][col]);
        }
        println!("");
    }
}

//fn findChildren(board: )