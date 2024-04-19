## OCR Application using QT framework 

### Installation Dependencies
Tesseract
OpenCV
QT 5

These libraries should be available in search paths of the system


### Building and running Locally

```git clone https://github.com/7Mcking/OCRonQt.git```

```mkdir build &&  cd build```

```cmake ..```

```make```

```./OCR```

### Application 

- Can run directly with tesseract or run an EAST model to first find the text area in the image and then running OCR.
- Section of image can also be directly posted. However, its a work in progress.

![Alt text](https://github.com/7Mcking/OCRonQt/blob/main/Resources/OCR.png)
