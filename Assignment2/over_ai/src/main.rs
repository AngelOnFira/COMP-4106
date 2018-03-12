use std::process;

fn main() {

    //1 is my units
    //2 is enemy space
    //0 is empty space
    let mut board: [[i8;6]; 6] = [
    [2,0,2,0,0,1],
    [1,1,1,1,1,1],
    [1,1,1,1,1,1],
    [2,2,2,2,2,2],
    [2,2,2,2,2,2],
    [2,2,2,2,2,2]];

    for i in (0..10 + 1).rev() {
        println!("{}", i);
    }

    find_possible_moves(board)
}

//fn minimax(board: [[i8;6]; 6])

fn find_possible_moves(board: [[i8;6]; 6]) {
    //let mut children_to_add = Vec::new();
    let mut children = Vec::new();
    //let empty_spaces = 0;

    let mut last_board = board;
    let row = 0;
    let col = 5;
    print_board(board);
    println!("");
    println!("");

    //for row in 0..board.len() - 1 {
        //for col in 0..board[0].len() - 1 {
            if board[row][col] == 1 {
                //Simulates a piece being pushed all the way to one side
                let mut child_board = board;
                'outer: for left in (0..col + 1).rev() {
                    let mut last = 0;
                    //Simulates one push
                    'inner: for remove in (0..left + 1).rev() {
                        let curr = child_board[row][remove];
                        child_board[row][remove] = last;
                        last = curr;
                        //Check if we have just pushed into an empty position
                        if last == 0 {
                            print_board(child_board);
                            println!("left: {}", left);
                            println!("remove: {}", remove);
                            println!("last: {}", last);
                            println!("pushed empty");
                            println!("");
                            println!("");
                            break 'inner;
                        }
                    }
                    //Break to outer if we have pushed one of our own off
                    //the board, don't add it to children to look at
                    if last == 1 {
                        print_board(child_board);
                        println!("left: {}", left);
                        println!("last: {}", last);
                        println!("pushed our own");
                        println!("");
                        println!("");
                        break 'outer;
                    }
                    //If we pushed an enemy off the board, add as a
                    //child
                    else if last == 2 {
                        print_board(child_board);
                        println!("left: {}", left);
                        println!("last: {}", last);
                        println!("pushed off enemy");
                        children.push(child_board);
                        println!("");
                        println!("");
                    }
                }
                while !children.is_empty() {
                    let child = children.pop().unwrap();
                    print_board(child);
                    //for i in 0..row;
                }
                process::exit(1);


                /*
                for down in row..board.len() - 1 {
                    if board[row][col]
                }
                for left in 0..col {
                    if board[up][col] 
                }
                for right in col..board[0].len() - 1 {
                    if board[row][col]
                }
                */
            }
        //}
    //}
}

/*
fn create_child(row: bool, index: i8, start: i8, offset: i8) {

}
*/

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