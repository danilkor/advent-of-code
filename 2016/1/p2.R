library(stringr)
lines <- readLines("./input.txt")
elements <- c()
for (line in lines) {
  line <- str_replace_all(line, " ", "")
  elements <- c(elements, unlist(strsplit(line, ",")))
}

posx <- posy <- 0 # y north x east
direction <- 0 # 0 - north, clockwise

xpoints <- ypoints <- c()
found <- FALSE
for (element in elements) {
  if (substr(element, 1, 1) == "L") {
    direction <- direction - 1
  } else {
    direction <- direction + 1
  }
  if (direction > 3) {
    direction <- 0
  } else if (direction < 0) {
    direction <- 3
  }

  distance <- as.integer(substr(element, 2, 100))

  while (distance > 0) {
    distance <- distance - 1
    if (direction == 0) {
      posy <- posy + 1
    } else if (direction == 1) {
      posx <- posx + 1
    } else if (direction == 2) {
      posy <- posy - 1
    } else if (direction == 3) {
      posx <- posx - 1
    }

    for (i in seq_along(xpoints)){
      if (posx == xpoints[i] && posy == ypoints[i]) {
        print(posx)
        print(posy)
        cat("Distance: ", abs(posx)+abs(posy), "\n")
        xpoints <- append(xpoints, posx)
        ypoints <- append(ypoints, posy)
        found <- TRUE
        break
      }
      if (found) {
        break
      }
    }
    if (found) {
      break
    }
    xpoints <- append(xpoints, posx)
    ypoints <- append(ypoints, posy)  
  }
  if (found) {
    break
  } 
}
plot(xpoints, ypoints, type="l", lwd=3)
points(0, 0, cex=1, pch=16, col="red")
points(posx, posy, cex=1, pch=16, col="blue")
lines(c(0, posx), c(0, posy), type="l")