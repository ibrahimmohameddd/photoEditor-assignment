// Students:                          IDs:               Filters:
// 1- Youssef Ehab Ahmed        -     20242428     -     grayScale / flipImage
// 2- Ibrahim Mohamed Hosny     -     20250006     -     blackAndWhite / rotateImage
// 3- Seif Khaled Ragab         -     20251205     -     invertImage / darkenAndLighten
// 4- Youssef Saied Helmy       -     20251496     -     addFrame / imageResize



#include <algorithm>
#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include "Image_Class.h"

using namespace std;

void grayscale(Image &image)
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0;

            for (int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k);
            }

            avg /= 3;

            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
}

void flipImage(Image &image)
{
    short choice;

    cout << "Press 1 for horizontal flip\n";
    cout << "Press 2 for vertical flip\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        for(int i = 0; i < image.width/2;i++){
            for(int j = 0; j <image.height;j++){
                for(int k = 0; k <3; k++){
                    unsigned char temp = image(i,j,k);
                    image(i,j,k) = image(image.width-i-1,j,k);
                    image(image.width-i-1,j,k) = temp;
                }
            }
        }
    };
    break;

    case 2:
    {
        for (int j = 0; j < image.height / 2; j++)
        {
            for (int i = 0; i < image.width; i++)
            {
                for (int k = 0; k < 3; k++)
                {
                    unsigned char temp = image(i, j, k);
                    image(i,j,k) = image(i,image.height-j-1,k);
                    image(i,image.height-1-j,k) = temp;
                }
            }
        }
    }

    }
}

void blackAndWhite(Image& image) {
    for(int y = 0; y < image.height; ++y) {
        for(int x = 0; x < image.width; ++x) {
            int r = image.getPixel(x, y, 0);
            int g = image.getPixel(x, y, 1);
            int b = image.getPixel(x, y, 2);

            int avg = (r + g + b) / 3;
            if(avg < 128) {
                image.setPixel(x, y, 0, 0);
                image.setPixel(x, y , 1, 0);
                image.setPixel(x, y, 2, 0);
            } else {
                image.setPixel(x, y, 0, 255);
                image.setPixel(x, y , 1, 255);
                image.setPixel(x, y, 2, 255);
            }
        }
    }
}

void rotateImage(Image& image, int angle) {
    int height = image.height;
    int width = image.width;
    int newWidth = width, newHeight = height;

    if(angle == 0) return;
    if(angle == 90 || angle == 270) {newWidth = height; newHeight = width;}
    else if(angle == 180) {newWidth= width; newHeight = height;}
    else return;

    Image temp(newWidth, newHeight);

    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            int newX = 0, newY = 0;
            if(angle == 90 ) {newX = height - 1 - y; newY = x;}
            if(angle == 180) {newX = width - 1 - x; newY = height - 1 - y;}
            if(angle == 270) {newX = y; newY = width - 1 - x;}

            int r = image.getPixel(x, y, 0);
            int g = image.getPixel(x, y, 1);
            int b = image.getPixel(x, y, 2);

            temp.setPixel(newX, newY, 0, r);
            temp.setPixel(newX, newY, 1, g);
            temp.setPixel(newX, newY, 2, b);
        }
    }

    image = temp;
}

void invertImage(Image& image){
    for(int y=0;y<image.height;y++){
        for(int x=0;x<image.width;x++){
            int r=255-image(x,y,0);
            int g=255-image(x,y,1);
            int b=255-image(x,y,2);
            image(x,y,0)=r;
            image(x,y,1)=g;
            image(x,y,2)=b;
            }
    }
}

void darkAndlightImage(Image& image, int percentage, int choice)
{
    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            int r = image(x, y, 0);
            int g = image(x, y, 1);
            int b = image(x, y, 2);

            if (choice == 1)
            {
                r = r + (255 - r) * percentage / 100;
                g = g + (255 - g) * percentage / 100;
                b = b + (255 - b) * percentage / 100;
            }
            else if (choice == 2)
            {
                r = r - r * percentage / 100;
                g = g - g * percentage / 100;
                b = b - b * percentage / 100;
            }

            image(x, y, 0) = r;
            image(x, y, 1) = g;
            image(x, y, 2) = b;
        }
    }
}

void resizeImage(Image& image, int new_width, int new_height)
{
    Image result(new_width, new_height);

    for (int y = 0; y < new_height; y++)
    {
        for (int x = 0; x < new_width; x++)
        {
            int x_original = x * image.width / new_width;
            int y_original = y * image.height / new_height;

            result(x, y, 0) = image(x_original, y_original, 0);
            result(x, y, 1) = image(x_original, y_original, 1);
            result(x, y, 2) = image(x_original, y_original, 2);
        }
    }

    image = result;
}

void addFrame(Image& image, int frame, int type){
    try{
        int newWidth = image.width + (2*frame);
        int newHeight = image.height + (2*frame);
        Image border_img(newWidth,newHeight);

        if(type == 1){
            for(int w =0;w<image.width;w++){
                for(int h = 0;h<image.height;h++){
                    int red = image.getPixel(w,h,0);
                    int green = image.getPixel(w,h,1);
                    int blue = image.getPixel(w,h,2);

                    border_img.setPixel(w+frame,h+frame,0,red);
                    border_img.setPixel(w+frame,h+frame,1,green);
                    border_img.setPixel(w+frame,h+frame,2,blue);
                }
            }
        }
        else{
            int thin = max(1, frame / 10);
            int outer = max(0, frame - 3 * thin);

            for(int x = 0; x < newWidth; x++){
                for(int y = 0; y < newHeight; y++){
                    bool insidePhoto = x >= frame && x < frame + image.width &&
                                       y >= frame && y < frame + image.height;

                    int r, g, b;

                    if(insidePhoto){
                        r = image.getPixel(x - frame, y - frame, 0);
                        g = image.getPixel(x - frame, y - frame, 1);
                        b = image.getPixel(x - frame, y - frame, 2);
                    }
                    else{
                        int d = min(min(x, y), min(newWidth - 1 - x, newHeight - 1 - y));
                        int color;

                        if(d < outer) color = 0;
                        else if(d < outer + thin) color = 255;
                        else if(d < outer + 2 * thin) color = 0;
                        else color = 255;

                        r = color;
                        g = color;
                        b = color;
                    }

                    border_img.setPixel(x, y, 0, r);
                    border_img.setPixel(x, y, 1, g);
                    border_img.setPixel(x, y, 2, b);
                }
            }
        }

        image = border_img;
    }
    catch(const exception& y){
        cerr<<"ERROR!!"<<y.what();
    }
}

stack<Image> versions;
string filename;
bool isSaved = true;
bool imageLoaded = false;
Image image;

void saveImage() {
    int choice;

    cout << "Press 0 to exit save menu: \n";
    cout << "Press 1 to save in the same file: \n";
    cout << "Press 2 to save in a new file: \n";

    cin >> choice;

    if(choice == 1 || choice == 2) isSaved = true;
    if(choice == 0) {
        cout << "Exiting save menu";
    }
    else if(choice == 1) image.saveImage(filename);
    else if(choice == 2) {
        string newFile;
        cout << "Enter new file name: \n";
        cin >> newFile;

        image.saveImage(newFile);
    }
}

int main() {

    while(true) {

        cout << "============================================\n";
        cout << "       IMAGE PROCESSING PROGRAM\n";
        cout << "============================================\n";
        cout << "Press 0 to exit program: \n";
        cout << "Press 1 to load an image: \n";
        cout << "Press 2 to apply filters: \n";
        cout << "Press 3 to undo changes: \n";
        cout << "Press 4 to save changes:\n";

        int input;
        cin >> input;

        if (input == 0) {
            cout << "Exiting program. \n";
            return 0;
        }

        else if (input == 1) {
            if(!isSaved) {
                cout << "There are some unsaved changes.\n";
                cout << "Press 0 to cancel\n";
                cout << "Press 1 to discard changes\n";
                cout << "Press 2 to save changes\n";
                int savingChoice;
                cin >> savingChoice;

                if (savingChoice == 0) {continue;}
                else if (savingChoice == 1) {}
                else if (savingChoice == 2) saveImage();
            }

            string newName;
            cout << "Enter image name: \n";
            cin >> newName;

            try {
                Image loadedImage(newName);
                image = loadedImage;
                filename = newName;
                imageLoaded = true;
                isSaved = true;

                while(!versions.empty()) versions.pop();

                cout << "Image loaded successfully. \n";
            }
            catch(...) {
                cout << "Failed to load image.\n";
            }
        }

        else if (input == 2) {

            if(!imageLoaded) {
                cout << "Please load an image first (option 1).\n";
                continue;
            }

            cout << "0. Exit filter menu\n";
            cout << "1. Grayscale\n";
            cout << "2. Black and White\n";
            cout << "3. Invert Image\n";
            cout << "4. Add Frame\n";
            cout << "5. Flip Image\n";
            cout << "6. Rotate Image\n";
            cout << "7. Darken or Lighten Image\n";
            cout << "8. Resize Image\n";

            int filterChoice;
            cin >> filterChoice;

            if(filterChoice >= 1 && filterChoice <= 8) {
                versions.push(image);
                isSaved = false;
            }

            switch (filterChoice) {

            case 0:
                cout << "Exiting filter menu.\n";
                continue;

            case 1:
                grayscale(image);
                cout << "Grayscale filter applied successfully.\n";
                break;

            case 2:
                blackAndWhite(image);
                cout << "Black and White filter applied successfully.\n";
                break;

            case 3:
                invertImage(image);
                cout << "Invert filter applied successfully.\n";
                break;

            case 4: {
                int frame, frameType;
                cout << "Enter the frame size: ";
                cin >> frame;

                cout << "1. Simple frame" << endl;
                cout << "2. Decorated frame" << endl;
                cout << "Choose: ";
                cin >> frameType;

                addFrame(image, frame, frameType);
                cout << "Frame added successfully.\n";
                break;
            }

            case 5:
                flipImage(image);
                cout << "Flip filter applied successfully.\n";
                break;

            case 6: {
                int angle;

                cout << "Enter rotation angle (90, 180, or 270): ";
                cin >> angle;

                rotateImage(image, angle);
                cout << "Rotate filter applied successfully.\n";
                break;
            }

            case 7: {
                int percentage;
                int choice;

                cout << "1. Lighten image" << endl;
                cout << "2. Darken image" << endl;
                cout << "Choose: ";
                cin >> choice;

                cout << "Enter percentage (0 - 100): ";
                cin >> percentage;

               
                    if (choice == 1)
                    {
                        darkAndlightImage(image, percentage, 1);
                    }
                    else if (choice == 2)
                    {
                        darkAndlightImage(image, percentage, 2);
                    }
                
                break;
            }

            case 8: {
                int newWidth, newHeight;

                cout << "Enter new width: ";
                cin >> newWidth;

                cout << "Enter new height: ";
                cin >> newHeight;
                resizeImage(image, newWidth, newHeight);
                cout << "Resize filter applied successfully.\n";
                break;
            }

            default:
                cout << "Invalid filter choice.\n";
                break;
            }
        }

        else if(input == 3) {

            if(!imageLoaded) {
                cout << "Please load an image first (option 1).\n";
                continue;
            }

            if(versions.empty()) {
                cout << "Nothing to undo.\n";
                continue;
            }

            image = versions.top();
            versions.pop();
            isSaved = false;
            cout << "Undo done.\n";
        }

        else if(input == 4) {

            if(!imageLoaded) {
                cout << "Please load an image first (option 1).\n";
                continue;
            }

            saveImage();
        }

        else {
            cout << "Invalid option.\n";
        }
    }
}
