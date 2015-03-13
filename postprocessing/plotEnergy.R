# Project 1
# Alina Dima and Mihai Fieraru
# Plotting eigenfaces after bin/varyEnergy executable has been successfully run and there exists the folder data/output


library(ggplot2)
library(reshape2)

o1 = read.csv("../data/output/output1.csv", sep = "\t")
o1.true = subset(o1, o1$First == 1 )
o1.false = subset(o1, o1$First == 0 )

par(mfrow=c(1,1))
plot(o1.true$Energy, o1.true$Accuracy, main = "Energy vs Accuracy", xlab = "Energy", ylab = "Accuracy", pch = 2)
points(o1.false$Energy, o1.false$Accuracy, col = "magenta")
legend("bottomright", c("present", "removed"), pch = c(2,1), title = "First eigenvector")

