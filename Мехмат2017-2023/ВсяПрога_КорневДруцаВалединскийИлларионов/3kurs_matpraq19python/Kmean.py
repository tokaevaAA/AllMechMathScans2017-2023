import numpy as np
import matplotlib.pyplot as plt

def make_graphic(data):
    plt.scatter(*data.T)
    plt.xlabel('Eruption time (min)')
    plt.ylabel('Waiting time til next eruption (min)')
    plt.show()
    
def make_graphic_classes(data,labels):
    plt.scatter(*data.T, c=np.where(labels, "blue", "orange"), s=20)
    plt.scatter(*centroids.T, c=["red", "green"], s=95, marker='*')
    plt.title('Predicted Classes')
    plt.show()
    
def mark_distances(data,centroids):
    raznost1=(data-centroids[0])
    raznost2=(data-centroids[1])
    distance=[]
    for i in range(0,len(raznost1),1):
        b=[np.linalg.norm(raznost1[i]),np.linalg.norm(raznost2[i])]
        distance.append(b)
    return distance

def get_label(data,centroids):
    
    dist=mark_distances(data,centroids)
    label=np.argmin(dist, axis=1)
    
    return label

def one_step(data,centroids,labels):
    #make_graphic_classes(data,labels)
    labels=get_label(data,centroids)
    print("labels: ",labels[0],labels[1],labels[2])
    #print(labels)
    #make_graphic_classes(data,labels)


    mask=(labels==0)
    center0=data[mask].mean(axis=0)
    mask=(labels==1)
    center1=data[mask].mean(axis=0)
    print("center0, center1: " ,center0,center1)

    centroids[0]=center0
    centroids[1]=center1
    
    
    return centroids


    
    

data = np.loadtxt('http://www.stat.cmu.edu/~larry/all-of-statistics/=data/faithful.dat', skiprows=26)[:, 1:]
#make_graphic(data,labels)

data=data-data.mean(axis=0);
data=data/data.std(axis=0)
print("data: ",data[0],data[1],data[2])

#centroids = np.random.uniform(-2, 2, 4).reshape((2, 2))
centroids=data[73:75:1]
oldcentroids=data[73:75:1]
print("centroids: ",centroids)

delta0=1
delta1=1
global labels
labels=np.ones(272)


print("start process:\n")



i=1

while(max(delta0,delta1)>0.000001):
    print("step=",i)
    i=i+1
    oldcentroids=centroids.copy()
    centroids=one_step(data,centroids,labels)
    #print("oldcentroids: ",oldcentroids)
    #print("centroids: ",centroids)
    delta0=np.linalg.norm(centroids[0]-oldcentroids[0])
    delta1=np.linalg.norm(centroids[1]-oldcentroids[1])
    print("delta0, delta1 : ",delta0,delta1)
    

with open ("output.txt","w") as f:
    f.write("Hello")
    



