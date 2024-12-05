#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <iostream>
#include <string>

using namespace std;

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

    // Перегрузка оператора ==
    bool operator==(const Track& other) const {
        return strcmp(this->title, other.title) == 0;
    }

    // Дружественная функция для вывода информации о треке
    friend ostream& operator<<(ostream& os, const Track& track) {
        os << track.title;
        return os;
    }
};

// Класс для хранения плейлиста
class Playlist {
private:
    Track* tracks;
    int total_number_of_tracks;
    int current_track;
    static int instance_count; // Статическое поле
public:
    Playlist() : total_number_of_tracks(0), current_track(0) {
        tracks = new Track[1];
        instance_count++;
    }

    ~Playlist() {
        delete[] tracks;
        instance_count--;
    }

    static int getInstanceCount() { // Статический метод
        return instance_count;
    }

    void viewSongs() {
        for (int i = 0; i < total_number_of_tracks; i++) {
            cout << i + 1 << ". " << tracks[i] << endl;
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

    void getSongByIndex(int index, Track*& song) { // Возврат через указатель
        if (index >= 0 && index < total_number_of_tracks) {
            song = &tracks[index];
        }
        else {
            song = nullptr;
        }
    }

    void getSongByIndex(int index, Track& song) { // Возврат через ссылку
        if (index >= 0 && index < total_number_of_tracks) {
            song = tracks[index];
        }
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
            // Если файл не найден, создаем его
            file = fopen(filename, "w");
            if (file == NULL) {
                throw runtime_error("Ошибка создания файла");
            }
            fclose(file);
            return;
        }

        char line[100];
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = 0;
            Track song;
            song.setTitle(line);
            addSong(song);
        }

        fclose(file);
    }

    void save_tracks_to_file(const char* filename) {
        FILE* file = fopen(filename, "w");
        if (file == NULL) {
            throw runtime_error("Ошибка открытия файла");
        }

        for (int i = 0; i < total_number_of_tracks; i++) {
            fprintf(file, "%s\n", tracks[i].getTitle());
        }

        fclose(file);
    }
};

int Playlist::instance_count = 0;

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