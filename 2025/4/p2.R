lines <- readLines("./input.txt")

matrix <- matrix()
matrix <- matrix[-c(1)]
for (line in lines) {
    matrix <- rbind(matrix, unlist(strsplit(trimws(line), '')))
}
#row, col
directions <- matrix(c(c(1,1), c(1,0), c(1,-1), c(0,1), c(0,-1), c(-1,1), c(-1,-1), c(-1,0)), ncol=2, byrow = TRUE)

rolls_number <- 0
moveable <- 0
mov <- list()

anyremoved <- TRUE

while(anyremoved){
    anyremoved <- FALSE
    for (row in seq_along(lines)) {
        for (col in 1:nchar(lines[1])) {
            aligned <- 0
            if (matrix[row,col] != '@') {
                next
            }
            for (i in 1:8) {
                tr <- row + directions[i,1]
                tc <- col + directions[i,2]
                tryCatch(
                    {
                        tr <- row + directions[i,1]
                        tc <- col + directions[i,2]
                        if (matrix[tr, tc] == '@') {
                            aligned <- aligned + 1
                        }
                        # print(paste("ROW: ", row, " COL: ", col))
                    }, error=function(e) {}
                )
            }

            if (aligned < 4) {
                moveable <- moveable + 1
                # mov <- append(mov, list(list(row,col)))
                matrix[row,col] <- "."
                anyremoved <- TRUE
            }
        }
    }
}
for (e in mov){
    e <- unlist(e)
    matrix[e[1],e[2]] <- "X"
}

print(moveable)