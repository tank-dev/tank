#include "Vector.hpp"

float operator*(Vector const& a, Vector const& b){
        return a.x*b.x + a.y*b.y;}
    
Vector operator*(Vector const& vect, float f){
    return {vect.x*f,vect.y*f};}
    
Vector operator+(Vector const& a, Vector const& b){
    return {a.x+b.x, a.y+b.y};}
Vector operator+(Vector const& vect, float f){
    return {vect.x+f, vect.y+f};}
Vector operator+(float f, Vector const& vect){
    return {vect.x+f, vect.y+f};}
    
Vector operator-(Vector const& a, Vector const& b){
    return {a.x-b.x,a.y-b.y};}
Vector operator-(Vector const& vect, float f){
    return {vect.x-f,vect.y-f};}
Vector operator-(float f, Vector const& vect){
    return {vect.x-f,vect.y-f};}
