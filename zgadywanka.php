
<?php
    $liczba_do_odgadniecia = 42;
    $liczba_prob = ($isset($_POST["liczba_prob"])) ? $_POST["liczba_prob"]
 + 1 : 1;
    if (!isset($_POST["liczba"])) {
        $komunikat = "Witaj w maszynie zgadującej!";
    } else if ($_POST["liczba"] > $liczba_do_odgadniecia) {
        $komunikat = "Liczba ".$_POST["liczba"]."jest zbyt duża, spróbuj mniejszej.";
    } else if ($_POST["liczba"] < $liczba_do_odgadniecia) {
        $komunikat = "Liczba ".$_POST["liczba"]." jest zbyt małą, spróbuj większej.";
    } else {
        $komunikat = "Gratulacje!";
    }
    $liczba = $_POST["liczba"];
    
?>

<!DOCTYPE html>
    <head>
        <meta charset="UTF-8">
        <title>Zachowywanie stanu w ukrytym polu</title>
    </head>
    <body>
        <h1><?php echo $komunikat ?></h1>
        <p><strong>Numer próby:</strong> <?php echo $liczba_prob ?></p>
        <form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="POST">
            <p><strong>Wybierz liczbę: </strong></p>
            <input type="text" name="liczba" value="<?php echo $liczba; ?>"/>
            <input type="hidden" name="liczba_prob" value="<?php echo $liczba_prob; ?>"/>
            <p><input type="submit" value="Wyślij"/></p>
        </form>
    </body>
</html>
