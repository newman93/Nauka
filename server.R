# Prosta aplikacja webowa
# Zbiór danych: Wydatki na sprzęt elektorniczny ze względu na płeć oraz status zawodowy

library(shiny)

myData <- read.table("dane.txt", sep = "\t", header = TRUE)

shinyServer(function(input, output) {
  
  formulaText <- reactive({
    paste("wydatki ~", input$variable)
  })
  
  output$caption <- renderText({
    formulaText()
  })
  
  output$wydatkiPlot <- renderPlot({
    boxplot(as.formula(formulaText()), 
          data = myData,
          outline = input$outliers,
          xlab = input$variable,
          ylab = "Wydatki (zł)")
  })
  
  output$statusPlot <- renderPlot({
      barplot(table(myData$status), main="Status zawodowy",  xlab="Status", ylab = "Ilość osób", col=rainbow(5))
  })
  
  output$płećPlot <- renderPlot({
      barplot(table(myData$płeć), main="Podział procentowy ze wględu na płeć",  xlab="Płeć", ylab = "Ilość osób", col=rainbow(2))
  })
  
  output$downloadData <- downloadHandler(
    filename = function() {
      paste('dane-', Sys.Date(), '.txt', sep='\t')
    },
    content = function(file) {
      write.table(myData, file)
    }
  )

})
