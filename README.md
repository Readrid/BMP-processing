# BMP Processing

Приложение вырезает из BMP-файла изображение в форме прямоугольника, поворачивает его на 90 градусов по часовой стрелке и сохраняет результат в отдельный файл.

## Консольное приложение
Приложение запускается следующей командой:
```
./bmp-processing crop-rotate ‹in-bmp› ‹out-bmp› ‹x› ‹y› ‹w› ‹h›
```
Используемые параметры:
  * ```crop-rotate``` — обязательный параметр, означающий выполняемое действие.
  * ```in-bmp``` — имя входного файла с изображением.
  * ```out-bmp``` — имя выходного файла с изображением.
  * ```x```, ```y``` — координаты левого верхнего угла области, которую необходимо вырезать и повернуть. Координаты начинаются с нуля, таким образом (0, 0) — это верхний левый угол.
  * ```w```, ```h``` — соотвественно, ширина и высота области до поворота.
