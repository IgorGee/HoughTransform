[h1]: http://i.imgur.com/x1cKR59.png "Edge Map"
[h2]: http://i.imgur.com/nAQ1A8t.png "Thresholding Result"
[h3]: http://i.imgur.com/Zicc2ks.png "Hough Space"
[h4]: http://i.imgur.com/oupENKS.png "Line Application"

# Hough Transform

The **Hough Transform** is a feature extraction technique used in image
analysis, computer vision, and digital image processing. The purpose of the
technique is to find imperfect instances of objects within a certain class
of shapes by a voting procedure. This voting procedure is carried out in a
parameter space, from which object candidates are obtained as local maxima
in a so-called accumulator space that is explicitly constructed by the
algorithm for computing the Hough Transform.

## H1

This program converts an image into an edge-map image. The method by which
the transformation happens is with the [Laplacian of Gaussian Filter](http://academic.mu.edu/phys/matthysd/web226/Lab02.htm).

![h1]

## H2

The next program is used to threshold out the weak edges as a result from
the previous program.

![h2]

## H3

This is where the application of the Hough Transform occurs. This program
will create a visual representation of the Hough Space, as well as a data
format representing that Hough Space.

![h3]

## H4

Now we are ready to use out generated Hough space in the original image.
This program will draw straight lines on the original image where it
detects lines from the Hough space.

![h4]

# Program Executions

`./h1 <input gray-level image> <output gray-level image>`

`./h2 <input gray-level image> <input gray-level threshold> <output binary image>`

`./h3 <input binary edge image> <output gray-level Hough image> <output Hough-voting-array>`

- threshold used for sample images: 3

`./h4 <input original gray-level image> <input Hough-voting-array> <input Hough threshold value> <output gray-level line image>`

- threshold used for sample images: 90
