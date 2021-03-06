use std::process;
extern crate rand;
use rand::{thread_rng, Rng};

pub static mut NODES_VISITED: i64 = 0;

fn main() {
    //1 is my units
    //2 is enemy space
    //0 is empty space
    
    for games in 0..5 {
        let mut board = create_board();

        let mut i = 0;
        while true {
            i += 1;
            board = ai_turn_enemy_children(board);
            //println!("Random Move");
            //print_board(board);
            if check_win(board) != 0 { println!("The AI wins"); break; }
            board = computer_turn(board);
            //println!("Heuristic Move");
            //print_board(board);
            if check_win(board) != 0 { println!("The Random wins"); break; }
            if i > 100 {
                break;
            }
        }

        unsafe {
            println!("Nodes visited {}", NODES_VISITED);
        }

        let mut i = 0;
        while false {
            i += 1;
            board = ai_turn_my_children(board);
            println!("First AI Move");
            print_board(board);
            if check_win(board) != 0 { println!("The first AI wins"); break; }
            board = ai_turn_enemy_children(board);
            println!("Second AI Move");
            unsafe {
            println!("Nodes visited {}", NODES_VISITED);
            }
            print_board(board);
            if check_win(board) != 0 { println!("The second AI wins"); break; }
            if i > 100 {
                break;
            }
        }
    }

    unsafe {
        println!("Nodes visited {}", NODES_VISITED);
    }
}

fn check_win(board: [[i8;6]; 6]) -> i8 {
    let mut player_1 = 0;
    let mut player_2 = 0;
    for row in 0..6 {
        for col in 0..6 {
            if board[row][col] == 1 {
                player_1 += 1;
            }
            if board[row][col] == 2 {
                player_2 += 1;
            }
            if player_1 != 0 && player_2 != 0 {
                return 0;
            }
        }
    }
    if player_1 == 0 {
        return 2;
    }
    if player_2 == 0 {
        return 1;
    }
    else {
        return 0;
    }
}

fn print_moves(moves: Vec<[[i8; 6]; 6]>) {
    for i in 0..moves.len() {
        println!("comp move");
        print_board(moves[i]);
    }
}

fn ai_turn_my_children(board: [[i8;6]; 6]) -> [[i8;6]; 6] {
    let mut moves = find_possible_moves(board, 1, 2);
    
    let mut curr_move = 0;
    let mut curr_score = 0.0;

    for i in 0..moves.len() {
        let score = alphabeta(moves[i], 2, -10000.0, 10000.0, true, 1, 2, 1);
        if score > curr_score {
            curr_score = score;
            curr_move = i;
        }
    }

    return moves[curr_move];
}

fn ai_turn_enemy_children(board: [[i8;6]; 6]) -> [[i8;6]; 6] {
    let mut moves = find_possible_moves(board, 1, 2);
    
    let mut curr_move = 0;
    let mut curr_score = 0.0;

    for i in 0..moves.len() {
        let score = alphabeta(moves[i], 2, -10000.0, 10000.0, true, 2, 1, 2);
        if score > curr_score {
            curr_score = score;
            curr_move = i;
        }
    }

    return moves[curr_move];
}

fn computer_turn(board: [[i8;6]; 6]) -> [[i8;6]; 6] {
    let mut moves = find_possible_moves(board, 2, 1);
    let mut rng = thread_rng();

    //for i in 0..moves.len() {
        //println!("comp move");
        //print_board(moves[i]);
    //}

    let rand_num: i8 = rng.gen_range(0, moves.len() as i8);
    return moves[rand_num as usize];
}

fn create_board() -> [[i8; 6]; 6] {
    let mut rng = thread_rng();
    let mut places = Vec::new();
    let mut board: [[i8;6]; 6] = [
    [2,2,2,2,2,2],
    [2,2,2,2,2,2],
    [2,2,2,2,2,2],
    [2,2,2,2,2,2],
    [2,2,2,2,2,2],
    [2,2,2,2,2,2]];

    for _piece in 0..18 {
        let mut new_place = false;
        while !new_place {
            new_place = true;
            let rand_num: i8 = rng.gen_range(0, 36);

            for i in 0..places.len() {
                if places[i] == rand_num {
                    new_place = false;
                    break;
                }
            }
            if new_place {
                places.push(rand_num);
            }
        }
    }

    while !places.is_empty() {
        let place = places.pop().unwrap();
        board[(place / 6) as usize][(place % 6) as usize] = 1;
    }

    print_board(board);

    return board;
}

fn alphabeta(board: [[i8;6]; 6], depth: i16, alpha_in: f32, beta_in: f32, max_player: bool, player_piece: i8, other_piece: i8, heuristic: i8) -> f32 {
    let mut alpha = alpha_in;
    let mut beta = beta_in;

    unsafe {
        if heuristic == 2 {
        NODES_VISITED += 1;
        }
    }

    let mut children = find_possible_moves(board, player_piece, other_piece);

    if depth == 0 {
        if heuristic == 1 {
            return children.len() as f32;
        }
        if heuristic == 2 {
            return 1.0 / find_possible_moves(board, other_piece, player_piece).len() as f32;
        }
    }

    if children.len() == 0 {
        if heuristic == 1 {
            return children.len() as f32;
        }
        if heuristic == 2 {
            return 1.0 / find_possible_moves(board, other_piece, player_piece).len() as f32;
        }
    }

    if max_player {
        let mut v = -10000 as f32;
        while !children.is_empty() {
            let child = children.pop().unwrap();
            v = max(v, alphabeta(child, depth - 1, alpha, beta, false, player_piece, other_piece, heuristic));
            alpha = max(alpha, v);
            if beta <= alpha {
                break;
            }
        }
        return v;
    }
    else {
        let mut v = 10000 as f32;
        while !children.is_empty() {
            let child = children.pop().unwrap();
            v = min(v, alphabeta(child, depth - 1, alpha, beta, true, player_piece, other_piece, heuristic));
            beta = min(beta, v);
            if beta <= alpha {
                break;
            }
        }
        return v;
    }
}

fn find_possible_moves(board: [[i8;6]; 6], player_piece: i8, other_piece: i8) -> Vec<[[i8; 6]; 6]> {
    let mut children = Vec::new();

    for row in 0..board.len() {
        for col in 0..board[0].len() {
            if board[row][col] == player_piece {
                //Simulates a piece being pushed all the way to one side
                let mut new_children = push_piece(row, col, board, player_piece, other_piece);
                while !new_children.is_empty() {
                    children.push(new_children.pop().unwrap());
                }
            }
        }
    }
    //println!("len {}", children.len());
    return children;
}

fn push_piece(row: usize, col: usize, board: [[i8;6]; 6], player_piece: i8, other_piece: i8) -> Vec<[[i8; 6]; 6]> {
    let mut children = Vec::new();
    let mut child_board = board;

    if row > 0 {
        if board[row - 1][col] == 0 {
            let mut new_board = board;
            new_board[row - 1][col] = player_piece;
            new_board[row][col] = 0;
            children.push(new_board);
        }
    }

    if row < 5 {
        if board[row + 1][col] == 0 {
            let mut new_board = board;
            new_board[row + 1][col] = player_piece;
            new_board[row][col] = 0;
            children.push(new_board);
        }
    }

    if col > 0 {
        if board[row][col - 1] == 0 {
            let mut new_board = board;
            new_board[row][col - 1] = player_piece;
            new_board[row][col] = 0;
            children.push(new_board);
        }
    }

    if col < 5 {
        if board[row][col + 1] == 0 {
            let mut new_board = board;
            new_board[row][col + 1] = player_piece;
            new_board[row][col] = 0;
            children.push(new_board);
        }
    }

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
                break 'inner1;
            }
        }
        //Break to outer if we have pushed one of our own off
        //the board, don't add it to children to look at
        if last == player_piece {
            break 'outer1;
        }
        //If we pushed an enemy off the board, add as a
        //child
        else if last == other_piece {
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
        if last == player_piece {
            break 'outer2;
        }
        //If we pushed an enemy off the board, add as a
        //child
        else if last == other_piece {
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
        if last == player_piece {
            break 'outer3;
        }
        //If we pushed an enemy off the board, add as a
        //child
        else if last == other_piece {
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
        if last == player_piece {
            break 'outer4;
        }
        //If we pushed an enemy off the board, add as a
        //child
        else if last == other_piece {
            children.push(child_board);
        }
    }
    return children;
}

fn get_heuristic(_board: [[i8;6]; 6]) -> f32 {
    //TODO
    return 1 as f32;
}

fn print_board(board: [[i8;6]; 6]) {
    println!("_____________");
    for row in 0..6 {
        for col in 0..6 {
            if board[row][col] == 0 {
                print!("| ");
            }
            else if board[row][col] == 1 {
                print!("|O");
            }
            else if board[row][col] == 2 {
                print!("|#");
            }
        }
        println!("|");
    }
    println!("_____________")
}

fn max(a: f32, b: f32) -> f32 {
    if a > b {
        return a;
    }
    else {
        return b;
    }
}

fn min(a: f32, b: f32) -> f32 {
    if a < b {
        return a;
    }
    else {
        return b;
    }
}

//fn findChildren(board: )