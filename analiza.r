# Autorzy: Adrian Kowalski, Arkadiusz Gugula, Marcel Ghayyeda
# Zbiór danych: Wydatki na sprzęt elektorniczny ze względu na płeć oraz status zawodowy

library(plotrix)

mydata <- read.table("dane.txt", sep = "\t", header = TRUE)
srednia_all <- mean(mydata[,"wydatki"])
mediana_all <- median(mydata[,"wydatki"])
standard_deviation_all <- sd(mydata[,"wydatki"])
mean_women <- mean(mydata[mydata$płeć != "mężczyzna", "wydatki"]) 
median_women <- median(mydata[mydata$płeć != "mężczyzna","wydatki"])
standard_deviation_women <- sd(mydata[mydata$płeć != "mężczyzna","wydatki"])
mean_men <- mean(mydata[mydata$płeć != "kobieta", "wydatki"])
median_men <- median(mydata[mydata$płeć != "kobieta","wydatki"])
standard_deviation_men <- sd(mydata[mydata$płeć != "kobieta","wydatki"])

women <- length(mydata$płeć[mydata$płeć == "kobieta"])
men <- length(mydata$płeć[mydata$płeć == "mężczyzna"])

slices <- c(women, men) 
lbls <- c("Kobieta", "Mężczyzna")

#podzial kobiety mężczyźni
pie3D(slices,radius=0.9,height=0.1,labels = c(round(women/(women+men)*100,1), round(men/(women+men)*100,1)),explode=0.1,main="Podział procentowy ze względu na płeć")
legend(0.2,0.98,lbls, fill = rainbow(2))

#podział status zawodowy
counts <- table(mydata$status)
barplot(counts, main="Status zawodowy",  xlab="Status", ylab = "Ilość osób", col=rainbow(5))

#średnie wydatki kobiety i mężczyźni
plot(mydata$płeć, mydata$wydatki, main="Wydatki w zależności od płci", xlab="Płeć", ylab="Wydatki (zł)")

#średnie wydatki status
plot(mydata$status, mydata$wydatki, main="Wydatki w zależności od statusu zawodowego", xlab="Status", ylab="Wydatki (zł)")
