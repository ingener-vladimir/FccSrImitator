ARG version=bionic
FROM theshadowx/qt5:${version} AS qt

LABEL author = "Sankov Vladimir" mail="v.n.sankov92@mail.ru"

RUN mkdir -p /app/projects

ENV gitUrl=https://github.com/ingener-vladimir/FccSrImitator.git  \
    branch=master \
    dir=/app

WORKDIR ${dir}

EXPOSE 9090

ENTRYPOINT git -C ${dir} clone $gitUrl \
                && cd ${dir}/FccSrImitator \
                && git checkout $branch \
                && qmake ${dir}/FccSrImitator/FccSrImitator.pro \
                && make \
                && LD_LIBRARY_PATH=${dir}/FccSrImitator/lib.linux/ \
                && export LD_LIBRARY_PATH \
                && ${dir}/FccSrImitator/bin/release/ControlStation/ControlStation \
                && /bin/sh
#CMD /bin/sh



