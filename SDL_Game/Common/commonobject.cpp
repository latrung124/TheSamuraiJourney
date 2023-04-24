#include "commonobject.h"

static CommonObject* common_object_ = nullptr;

CommonObject::CommonObject() {

}

CommonObject::~CommonObject() {

}

CommonObject* CommonObject::Instance(){
    if (common_object_ == nullptr) {
        common_object_ = new CommonObject();
    }
    return common_object_;
}
SDL_Texture* CommonObject::ImageTexture(std::string& _path, SDL_Renderer* _renderer) {
    if (_renderer == nullptr) {
        printf("%s renderer was nullptr!\n", __FUNCSIG__);
    }
    SDL_Surface* image_surface = IMG_Load(_path.c_str());
    if (image_surface == nullptr) {
        printf("%s () failed to load the image! SDL_Error(): %s\n", __FUNCSIG__, SDL_GetError());
        return nullptr;
    }
    SDL_Texture* image_texture = SDL_CreateTextureFromSurface(_renderer, image_surface);
    if (image_texture == nullptr) {
        printf("%s () failed to load the image texture! SDL_Error(): %s\n", __FUNCSIG__,  SDL_GetError());
        return nullptr;
    }
    //free surface after load it to the texture
    SDL_FreeSurface(image_surface);
    return image_texture;
}
