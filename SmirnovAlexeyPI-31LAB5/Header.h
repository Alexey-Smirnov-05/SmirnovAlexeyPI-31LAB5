#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Класс для хранения информации о треке
class Track {
private:
    char title[100];
public:
    Track() {}
    Track(const char* title) {
        strcpy(this->title, title);
    }
    char* getTitle() {
        return title;
    }
    void setTitle(const char* title) {
        strcpy(this->title, title);
    }
};

// Класс для хранения плейлиста
class Playlist {
private:
    Track* tracks;
    int total_number_of_tracks;
    int current_track;
public:
    Playlist() : total_number_of_tracks(0), current_track(0) {
        tracks = new Track[1];
    }
    ~Playlist() {
        delete[] tracks;
    }
    void viewSongs() {
        for (int i = 0; i < total_number_of_tracks; i++) {
            printf("%d. %s\n", i + 1, tracks[i].getTitle());
        }
    }
    void addSong(const Track& song) {
        Track* newTracks = new Track[total_number_of_tracks + 1];
        for (int i = 0; i < total_number_of_tracks; i++) {
            newTracks[i] = tracks[i];
        }
        newTracks[total_number_of_tracks] = song;
        delete[] tracks;
        tracks = newTracks;
        total_number_of_tracks++;
    }
    void removeSong(int index) {
        for (int i = index; i < total_number_of_tracks - 1; i++) {
            tracks[i] = tracks[i + 1];
        }
        total_number_of_tracks--;
        Track* newTracks = new Track[total_number_of_tracks];
        for (int i = 0; i < total_number_of_tracks; i++) {
            newTracks[i] = tracks[i];
        }
        delete[] tracks;
        tracks = newTracks;
    }
    int getTotalNumberOfTracks() {
        return total_number_of_tracks;
    }
    Track* getTracks() {
        return tracks;
    }
    int getCurrentTrack() {
        return current_track;
    }
    void setCurrentTrack(int current_track) {
        this->current_track = current_track;
    }
    void load_tracks_from_file(const char* filename) {
        FILE* file = fopen(filename, "r");
        if (file == NULL) {
            return;
        }

        char line[100];
        int i = 0;
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = 0;
            Track song;
            song.setTitle(line);
            addSong(song);
            i++;
        }

        fclose(file);
    }
    void save_tracks_to_file(const char* filename) {
        FILE* file = fopen(filename, "w");
        if (file == NULL) {
            return;
        }

        for (int i = 0; i < total_number_of_tracks; i++) {
            fprintf(file, "%s\n", tracks[i].getTitle());
        }

        fclose(file);
    }
};

// Класс для демонстрации признака ассоциаций
class User {
private:
    Playlist* playlist;
public:
    User(Playlist* playlist) : playlist(playlist) {}
    void addSongToPlaylist(const Track& song) {
        playlist->addSong(song);
    }
    void removeSongFromPlaylist(int index) {
        playlist->removeSong(index);
    }
    void viewPlaylist() {
        playlist->viewSongs();
    }
};


// Класс для хранения громкости
class Volume {
private:
    int volume;
public:
    Volume() : volume(50) {}
    void changeVolume(int new_volume) {
        if (new_volume >= 0 && new_volume <= 100) {
            volume = new_volume;
            printf("Громкость изменена на %d%%\n", volume);
        }
        else {
            printf("Неверная громкость\n");
        }
    }
};

// Класс для хранения воспроизведения
class Playback {
private:
    Playlist* playlist;
    int current_track;
public:
    Playback(Playlist* playlist, int current_track) : playlist(playlist), current_track(current_track) {}
    void playSong() {
        printf("Сейчас играет: %s\n", playlist->getTracks()[current_track].getTitle());
    }
};

// Класс для хранения паузы
class Pause {
private:
    Playlist* playlist;
public:
    Pause(Playlist* playlist) : playlist(playlist) {}
    void pauseSong() {
        printf("На паузе\n");
    }
};

// Класс для хранения перехода к следующему треку
class Skip {
private:
    Playlist* playlist;
public:
    Skip(Playlist* playlist) : playlist(playlist) {}
    void skipSong() {
        playlist->setCurrentTrack((playlist->getCurrentTrack() + 1) % playlist->getTotalNumberOfTracks());
        Playback playback(playlist, playlist->getCurrentTrack());
        playback.playSong();
    }
};

// Класс для хранения возврата к предыдущему треку
class Previous {
private:
    Playlist* playlist;
public:
    Previous(Playlist* playlist) : playlist(playlist) {}
    void previousSong() {
        playlist->setCurrentTrack((playlist->getCurrentTrack() - 1 + playlist->getTotalNumberOfTracks()) % playlist->getTotalNumberOfTracks());
        Playback playback(playlist, playlist->getCurrentTrack());
        playback.playSong();
    }
};

// Класс для хранения просмотра треков в плейлисте
class View {
private:
    Playlist* playlist;
public:
    View(Playlist* playlist) : playlist(playlist) {}
    void viewSongs() {
        for (int i = 0; i < playlist->getTotalNumberOfTracks(); i++) {
            printf("%d. %s\n", i + 1, playlist->getTracks()[i].getTitle());
        }
    }
};