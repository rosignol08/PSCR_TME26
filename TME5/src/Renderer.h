#pragma once

#include "Scene.h"
#include "Image.h"
#include "Ray.h"

#include "thread"
namespace pr {

// Classe pour rendre une scène dans une image
class Renderer {
public:
    // Rend la scène dans l'image
    void render(const Scene& scene, Image& img) {
        // les points de l'ecran, en coordonnées 3D, au sein de la Scene.
        // on tire un rayon de l'observateur vers chacun de ces points
        const Scene::screen_t& screen = scene.getScreenPoints();

        // pour chaque pixel, calculer sa couleur
        for (int y = 0; y < scene.getHeight(); y++) {
            for (int x = 0; x < scene.getWidth(); x++) {
                // le point de l'ecran par lequel passe ce rayon
                auto& screenPoint = screen[y][x];
                // le rayon a inspecter
                Ray ray(scene.getCameraPos(), screenPoint);

                int targetSphere = scene.findClosestInter(ray);

                if (targetSphere == -1) {
                    // keep background color
                    continue;
                } else {
                    const Sphere& obj = scene.getObject(targetSphere);
                    // pixel prend la couleur de l'objet
                    Color finalcolor = scene.computeColor(obj, ray);
                    // mettre a jour la couleur du pixel dans l'image finale.
                    img.pixel(x, y) = finalcolor;
                }
            }
        }
    }
    void renderThreadPerPixel(const Scene& scene, Image& img){
        std::vector <std::thread> workers;
        //workers.reserve(scene.getHeight() * scene.getWidth());
        // les points de l'ecran, en coordonnées 3D, au sein de la Scene.
        // on tire un rayon de l'observateur vers chacun de ces points
        const Scene::screen_t& screen = scene.getScreenPoints();
        int cpt = 0;
        // pour chaque pixel, calculer sa couleur
        for (int y = 0; y < scene.getHeight(); y++) {
            for (int x = 0; x < scene.getWidth(); x++) {
                //je crée le thread
                workers.push_back(std::thread([this, &scene, &img, &screen, x,y]() {
                    // le point de l'ecran par lequel passe ce rayon
                    auto& screenPoint = screen[y][x];
                    // le rayon a inspecter
                    Ray ray(scene.getCameraPos(), screenPoint);

                    int targetSphere = scene.findClosestInter(ray);

                    if (targetSphere == -1) {
                        // keep background color
                    } else {
                        const Sphere& obj = scene.getObject(targetSphere);
                        // pixel prend la couleur de l'objet
                        Color finalcolor = scene.computeColor(obj, ray);
                        // mettre a jour la couleur du pixel dans l'image finale.
                        img.pixel(x, y) = finalcolor;
                    }}));
                    cpt++;
                //ici on a fini de remplir le thread
            }
        }
        for(int i = 0; i < cpt; ++i){
            workers[i].join();
        }

    }
    
    void renderThreadPerRow(const Scene& scene, Image& img){
        std::vector <std::thread> workers;
        //workers.reserve(scene.getHeight() * scene.getWidth());
        // les points de l'ecran, en coordonnées 3D, au sein de la Scene.
        // on tire un rayon de l'observateur vers chacun de ces points
        const Scene::screen_t& screen = scene.getScreenPoints();
        int cpt = 0;
        // pour chaque pixel, calculer sa couleur
        for (int y = 0; y < scene.getHeight(); y++) {
                //je crée le thread
                workers.push_back(std::thread([this, &scene, &img, &screen, y]() {
                    // le point de l'ecran par lequel passe ce rayon
                    for (int x = 0; x < scene.getWidth(); x++) {
                        auto& screenPoint = screen[y][x];
                        // le rayon a inspecter
                        Ray ray(scene.getCameraPos(), screenPoint);

                        int targetSphere = scene.findClosestInter(ray);

                        if (targetSphere == -1) {
                            // keep background color
                        } else {
                            const Sphere& obj = scene.getObject(targetSphere);
                            // pixel prend la couleur de l'objet
                            Color finalcolor = scene.computeColor(obj, ray);
                            // mettre a jour la couleur du pixel dans l'image finale.
                            img.pixel(x, y) = finalcolor;
                        }
                    }}));
                    cpt++;
        }
        for(int i = 0; i < cpt; ++i){
            workers[i].join();
        }

    }


    void renderThreadManual(const Scene& scene, Image& img, int nbthread){
        std::vector <std::thread> workers;
        const Scene::screen_t& screen = scene.getScreenPoints();
        //int cpt = 0;
        int nb_tranches_hauteur = scene.getHeight() / nbthread;
        int nb_tranches_largeur = scene.getWidth() / nbthread;
        int minx = 0;
        int miny = 0;
        int maxx = 0;
        int maxy = 0;
        // pour chaque pixel, calculer sa couleur
        for (int i = 0; i < nbthread; i++) {
            minx = 0;
            miny = (i * scene.getHeight()) / nbthread;
            
            maxx = scene.getWidth();
            //t * H / N inclus à (t + 1) * H / N
            if(i == nbthread){
                maxy = scene.getHeight();
            }else{
                maxy = ((i+1) * scene.getHeight()) / nbthread;
            }
            std::cout << " thread : " << i << " minx : " << minx << " miny : " << miny <<  " maxx : " << maxx << " maxy : " << maxy << std::endl;
            //je crée le thread
            workers.push_back(std::thread([this, &scene, &img, &screen, minx, miny, maxx, maxy]() {
                    // le point de l'ecran par lequel passe ce rayon
                    for (int y = miny; y < maxy; y++) {
                        for (int x = minx; x < scene.getWidth(); x++) {
                            auto& screenPoint = screen[y][x];
                            // le rayon a inspecter
                            Ray ray(scene.getCameraPos(), screenPoint);

                            int targetSphere = scene.findClosestInter(ray);

                            if (targetSphere == -1) {
                                // keep background color
                            } else {
                                const Sphere& obj = scene.getObject(targetSphere);
                                // pixel prend la couleur de l'objet
                                Color finalcolor = scene.computeColor(obj, ray);
                                // mettre a jour la couleur du pixel dans l'image finale.
                                img.pixel(x, y) = finalcolor;
                            }
                        }
                    }}));
                }
        for(int i = 0; i < nbthread; ++i){
            workers[i].join();
        }

    }
    
};

} // namespace pr