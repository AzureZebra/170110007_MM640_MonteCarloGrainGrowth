function [] = EvolutionVideo()
B = csvread('abu_1.csv')+1;
A = length(colormap)*B/7;
%length(colormap);
colormap jet;
cmap = colormap;
%video writer
writerObj = VideoWriter('GrainGrowth_abu_1_jet.mj2');
writerObj.FrameRate = 20;
%sec per image is 0.1
secPerImage = zeros(1,4000)+0.1;

open(writerObj);
        
%i is each time instant
for i = 1:1:4000
    
    Array = A(i,:);

    %each time instant converted into matrix
    L=zeros(100,100);
    for x = 1:1:100
        for y = 1:1:100
            L(x,y) = Array(100*(x-1)+y);
        end
    end

    frame = im2frame(L,cmap);
    for v = 0:(secPerImage(i))
        writeVideo(writerObj,frame);
    end
                 
end
close(writerObj);
    
end

