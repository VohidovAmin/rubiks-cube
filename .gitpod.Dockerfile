FROM gitpod/workspace-full

USER root

RUN apt-get update \
    && apt-get install -y \
        freeglut3-dev \
        x11vnc \
        xvfb \
        fluxbox \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

USER gitpod

# Настройка x11vnc
RUN mkdir -p ~/.vnc \
    && x11vnc -storepasswd "gitpod" ~/.vnc/passwd

# Установка скрипта запуска
RUN echo 'xvfb-run -s "-screen 0 1024x768x16" fluxbox &' > ~/.gitpod_start \
    && echo 'x11vnc -forever -usepw -shared -rfbport 5900 &' >> ~/.gitpod_start \
    && echo './rubiks_cube' >> ~/.gitpod_start \
    && chmod +x ~/.gitpod_start

ENTRYPOINT ["/bin/bash", "-c", "~/.gitpod_start"]
