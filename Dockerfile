FROM alpine:3.19.1

ARG USER=default
ENV HOME /home/$USER

RUN apk add cmake gcc make musl-dev g++ sudo

RUN adduser -D $USER \
        && echo "$USER ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/$USER \
        && chmod 0440 /etc/sudoers.d/$USER

USER $USER
