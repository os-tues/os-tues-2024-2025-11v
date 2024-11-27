# Домашна работа №1

Домашна работа №1 включва задачи свързани с файлове, файлови дескриптори и системните
функции за работа с тях, които сме разглеждали до момента - `open`, `close`, `read`,
`write` и `lseek`. Състои се от 2 задачи и има максимален брой точки 400. Оценката
се изчислява по следната формула:

```plaintext
оценка = 2 + (точки / 100)
```

Срокът на домашната работа е **до 08.12.2024 (Неделя), 23:59:59**.

## ⚠️ ВАЖНО ⚠️

Напомням ви, че домашното ще бъде проверявано за плагиатство! Това включва и използването
на text-transformer невронни мрежи за написването решенията си, като ChatGPT, GitHub
Copilot и подобни услуги за генериране на код. Ако случайно сте почнали домашното
и casually сте се възползвали от такива услуги, това, което искам да направите е:

- Да спрете Copilot/каквото друго ползвате
- Да изтриете целия код, който имате досега
- Да почнете начисто и да си работите самостоятелно, като всякакъв код, копиран
  от някъде, да бъде ясно деклариран като коментар и по време на евентуална защита.

Имайте предвид, че невронните мрежи не са магия - реално са доста детерминистични
в изхода си и генерират доста сходен код, който после лесно се забелязва при проверката
за еднаквост на домашните ви.

Също така, важно е да отбележа, че преди крайния срок всякакво споделяне на решения
е забранено.

Това включва:

- Да пратите решението си на някой друг.
- Да го покажете на другарче, за да "почерпи идеи".
- Да го сложите някъде публично преди крайния срок.

От друга страна, не се притеснявайте да напишете най-простия възможен код, понеже
"други хора ще предадат същото решение". Това също се разпознава лесно, и разбира
се, няма да сметна, че сте преписвали. Пишете най-добрия код, на който сте способни,
не споделяйте решенията си и няма да има причина да се притеснявате, че ще помислим,
че сте преписвали.

Ако ви е нужна помощ с каквото и да е - разбиране на условието, кодът, качването
му и т.н., не се притеснявайте да се свържете с мен в по
имейл на `ibozhilov@elsys-bg.org`.


---


# Задача 1 - `lseek-decode` (200 точки)

- Целта на задачата е да се реализира parser за абстрактна блокова система, който
  да извежда информацията на стандартния изход (stdout). Системата се състои от
  множество структури (блокове) съдържащи в себе си информация и адрес (отместване
  от началото на файла) на следващия блок. Приемете, че един `block` е дефиниран
  по следния начин:

  ```c
  typedef struct {
      char data;
      unsigned char next_element_address;
  } block;
  ```

- Размерът на цялата система е 128 блока, а краят ѝ се разпознава по това, че в
  полето за адрес е записанo числото `0`. В началото на файла е записан първия блок.

- Пример за изпълнението на програмата:

  ```bash
  $ ./lseek-decode example-inputs/secret-message.hidden
  <some hidden message :)>
  ```

- Програмата ви трябва да обработва грешки при отваряне и четене на файла.

  ```bash
  $ ./lseek-decode nonexistent.txt
  ./sh: nonexistent.txt: No such file or directory
  ```

- За реализацията на програмата трябва да използвате `lseek` системната функция,
  заедно с `open`, `close`, `read` и `write`.

- Не е позволено използването на библиотечни функции като `fopen`, `fclose`, `fread`,
  `fwrite` и т.н.



---



# Задача 2 - `tail` (200 точки)

- Напишете програма на C, аналогична със системната команда tail.

- Програмата трябва да приема поне един задължителен команден аргумент - имената на вече
  съществуващи текстови файлове.

- Програмата трябва да извежда последните 10 реда от всеки файл.

- Ако във файл има по-малко от 10 реда, цялото му съдържание се извежда.

- Например, ако са дадени два файла със следното съдържание `example-inputs/a.txt`:

  ```plaintext
  one
  two
  three
  four
  five
  six
  seven
  eight
  nine
  ten
  eleven
  ```

  и `example-inputs/b.txt`:

  ```plaintext
  1234 1234
  567
  890
  ```

  и c.txt не съществува, тогава програмата трябва да изведе:

  ```bash
  $ ./tail example-inputs/a.txt example-inputs/b.txt example-inputs/c.txt
  ==> example-inputs/a.txt <==
  two
  three
  four
  five
  six
  seven
  eight
  nine
  ten
  eleven

  ==> example-inputs/b.txt <==
  1234 1234
  567
  890
  ./tail: cannot open 'example-inputs/c.txt' for reading: No such file or directory
  ```

- При наличието само на един аргумент, заглавната секция (секцията от типа
  `==> <име> <==`) се пропуска.

- Ако някой от аргументите на `tail` не е файл или файлът не може да се отвори,
  то програмата трябва да изведе съобщение на стандартния изход за грешка (stderr).

  Например, ако бъдат предадени аргументи, които не са файлове:

  ```bash
  ./tail aa bb
  ```

  съобщението трябва да бъде оформено по следния начин:

  ```bash
  ./tail: cannot open 'aa' for reading: No such file or directory
  ./tail: cannot open 'bb' for reading: No such file or directory
  ```

- Ако `./tail` не може да запише прочетеното на стандартния изход, то програмата
  трябва да изведе съобщение на стандартния изход за грешка (stderr). Например,
  ако дискът е пълен:

  ```bash
  ./tail example-inputs/a.txt > /dev/full
  ```

  съобщението трябва да бъде оформено по следния начин:

  ```bash
  ./tail: error writing 'standard output': No space left on device
  ```

- Ако `./tail` не може да затвори успешно някой файл, то програмата трябва да изведе
  съобщение на стандартния изход за грешка (stderr). Например:

  ```bash
  ./tail example-inputs/b.txt
  ```

  съобщението трябва да бъде оформено по следния начин:

  ```bash
  ./tail: error reading 'example-inputs/b.txt': Input/output error
  ```

- При грешка в един файл, то изпълнението трябва да продължи към следващите (програмата
  не трябва да приключи).

- За реализацията на програмата трябва да използвате `lseek` системната функция,
  заедно с `open`, `close`, `read` и `write`.

- Не е позволено използването на библиотечни функции като `fopen`, `fclose`, `fread`,
  `fwrite` и т.н.